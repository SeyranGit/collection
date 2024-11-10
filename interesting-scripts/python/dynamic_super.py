class BaseList(list):
  def __setitem__(self, key, value):
    print('In BaseList __setitem__')
    super().__setitem__(key, value)


class BaseDict(dict):
  def __setitem__(self, key, value):
    print('In BaseDict __setitem__')
    super().__setitem__(key, value)


def setitem(self, key, value):
  print('In setitem')
  super(type(self), self).__setitem__(key, value)


class List(BaseList):
  __setitem__ = setitem


class Dict(BaseDict):
  __setitem__ = setitem
  

my_list = List([0, 0, 0])
my_list[0] = 1

my_dict = Dict()
my_dict['name'] = 'Seyran'

print(my_list)
print(my_dict)
