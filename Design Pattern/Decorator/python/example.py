def decorator(original_function):
    import time
    
    def wrapper():
        t0 = time.time()
        original_function()
        print(f'\n{original_function.__name__} has been run for {time.time() - t0} seconds')

    return wrapper


def helloworld():

    for i in range(10):
        print('Hello, World!')


my_helloworld = decorator(helloworld)

my_helloworld()

