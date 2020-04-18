#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include<cstring>

extern "C" void SlowFunc();

void* handle;
void (*func_from_dl)(const std::string&);

int main(int argc, char *argv[]) {
	SlowFunc();
	if (argc != 2) {
		return 1;
	} else {
		if (std::strcmp(argv[1], "h") == 0) {
			// GetHours
			handle = dlopen("libhour.so", RTLD_LAZY);
			if(!handle)
			{
				fprintf(stderr, "Error: %s\n", dlerror());
				return EXIT_FAILURE;
			}

			*(void**)(&func_from_dl) = dlsym(handle, "GetHours");
		} else if (std::strcmp(argv[1], "c") == 0) {
			// GetCost
			handle = dlopen("libcost.so", RTLD_LAZY);

			if(!handle)
			{
				fprintf(stderr, "Error: %s\n", dlerror());
				return EXIT_FAILURE;
			}

			*(void**)(&func_from_dl) = dlsym(handle, "GetCost");
		}

		if(!func_from_dl)
		{
			fprintf(stderr, "Error: %s\n", dlerror());
			dlclose(handle);
			return EXIT_FAILURE;
		}

		func_from_dl("2020-05-06");
		dlclose(handle);
	}
	return 1;
}

