# DLLFileExtractor
USAGE: DLLFileExtractor <Memory_dump_path> <Output_directory> <Size_of_largest_DLL>

Processes memory dump files to extract DLLs from them. Current implementation takes in
three parameters: the path to your memory dump file, the directory in which you want to
output the seperated DLL files, and file size to have each of them be. The file size
parameter tells the program how many bytes it should pass on to the file writing class
after detecting what it percieves to be a valid DLL.

Read more about this tool at my eng⁻¹ blog: http://eng-1.info/Extracting-DLLs-From-Memory
