# DD Image

DD Image is a c++ application for search and delete duplicate images.
DD Image explore the paths from the parent folder and his childs folders.
Read all images and search for duplicates at pixel level.
Remove the duplicate images.
Explore the code, you can use it for other tasks like compare images without remove them.
## Supported formats(you can include more in allowed_types.txt file):

* [jpg]
* [png]

## Requirements

* OpenCV c++ Version >= 3.3

## Installation

```bash
mkdir build
cd buid
cmake ..
make
```
## Usage

```bash
./DDImage /path_to_folder_whit_images path_to_allowed_types.txt
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.
