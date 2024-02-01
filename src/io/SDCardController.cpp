#include "io/SDCardController.h"
#ifdef PICO

bool SDCardController::write_file(std::string dir, std::string filename, const std::vector<uint8_t>* bytes)
{
	if (!mount() || !set_directory(dir)) return false;
	FIL file;
	FRESULT fr = f_open(&file, filename.c_str(), FA_CREATE_ALWAYS | FA_WRITE);
	if (FR_OK != fr) {
		std::cout << "f_open error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		unmount();
		return false;
	}

	UINT bytes_written;
	fr = f_write(&file, bytes->data(), bytes->size(), &bytes_written);
	std::cout << "Wrote " << bytes_written << " bytes" << std::endl;
	if (bytes_written != bytes->size()) {
		std::cout << "f_write error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl
				  << "Wrote " << bytes_written << " bytes instead of " << bytes->size() << std::endl;
		unmount();
		return false;
	}

	fr = f_close(&file);
	if (FR_OK != fr) {
		std::cout << "f_close error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		unmount();
		return false;
	}
	unmount();
	return true;
}

bool SDCardController::read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes)
{
	if (!mount() || !set_directory(dir)) return false;
	FIL file;
	FRESULT fr = f_open(&file, filename.c_str(), FA_READ);
	if (FR_OK != fr) {
		std::cout << "f_open error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		unmount();
		return false;
	}

	// get the size of the file
	FILINFO fno;
	fr = f_stat(filename.c_str(), &fno);
	if (FR_OK != fr) {
		std::cout << "f_stat error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		unmount();
		return false;
	}

	// resize the vector to fit the file
	bytes->resize(fno.fsize);

	UINT bytes_read;
	fr = f_read(&file, bytes->data(), bytes->size(), &bytes_read);
	if (bytes_read != bytes->size()) {
		std::cout << "f_read error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl
				  << "Read " << bytes_read << " bytes instead of " << bytes->size() << std::endl;
		unmount();
		return false;
	}

	unmount();
	return true;
}

bool SDCardController::file_exists(std::string dir, std::string filename)
{
	if (!mount() || !set_directory(dir)) return false;
	FILINFO fno;
	FRESULT fr = f_stat(filename.c_str(), &fno);
	if (FR_OK != fr) {
		std::cout << "f_stat error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		unmount();
		return false;
	}
	unmount();
	return true;
}

bool SDCardController::dir_exists(std::string dir)
{
	if (!mount() || !set_directory(dir)) return false;
	unmount();
	return true;
}

std::vector<std::string> SDCardController::list_dir(std::string dir)
{
	std::vector<std::string> files;
	if (!mount() || !set_directory(dir)) return files;

	DIR dj;
	FILINFO fno;
	memset(&dj, 0, sizeof dj);
	memset(&fno, 0, sizeof fno);

	FRESULT fr = f_findfirst(&dj, &fno, ("/" + dir).c_str(), "*");
	if (FR_OK != fr) {
		std::cout << "f_findfirst error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		unmount();
		return files;
	}

	while (fr == FR_OK && fno.fname[0]) { /* Repeat while an item is found */
		files.push_back(std::string(fno.fname));

		fr = f_findnext(&dj, &fno); /* Search for next item */
	}

	fr = f_closedir(&dj);
	if (FR_OK != fr) {
		std::cout << "f_closedir error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		unmount();
		return files;
	}

	unmount();
	return files;
}

bool SDCardController::set_directory(std::string dir)
{
	FRESULT fr = f_stat(("/" + dir).c_str(), NULL);

	if (fr == FR_NO_FILE) {
		f_chdir("/");
		f_mkdir(dir.c_str());
	} else if (fr != FR_OK) {
		return false;
	}

	fr = f_chdir(("/" + dir).c_str());

	if (fr == FR_OK) return true;
	return false;
}

bool SDCardController::mount()
{
	sd_card_t* sd_card = sd_get_by_num(0);
	FRESULT fr = f_mount(&sd_card->fatfs, sd_card->pcName, 1);
	if (FR_OK != fr) {
		std::cout << "f_mount error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		return false;
	}
	return true;
}

bool SDCardController::unmount()
{
	sd_card_t* sd_card = sd_get_by_num(0);
	FRESULT fr = f_unmount(sd_card->pcName);
	if (FR_OK != fr) {
		std::cout << "f_unmount error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		return false;
	}
	return true;
}

#else

bool SDCardController::write_file(std::string dir, std::string filename, const std::vector<uint8_t>* bytes)
{
	// TODO: fix
	dir = "C:\\calculator\\" + dir;
	if (!std::filesystem::exists(dir)) std::filesystem::create_directory(dir);
	FILE* file = fopen((dir + "\\" + filename).c_str(), "wb");
	fwrite(bytes, sizeof(uint8_t), bytes->size(), file);
	fclose(file);
	return true;
}

bool SDCardController::read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes)
{
	// TODO: fix
	FILE* file = fopen(("C:\\calculator\\" + dir + "\\" + filename).c_str(), "rb");
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	bytes->resize(size);
	fseek(file, 0, SEEK_SET);
	fread(bytes, sizeof(uint8_t), size, file);
	fclose(file);
	return true;
}

bool SDCardController::file_exists(std::string dir, std::string filename)
{
	return std::filesystem::exists("C:\\calculator\\" + dir + "\\" + filename);
}

bool SDCardController::dir_exists(std::string dir)
{
	return std::filesystem::exists("C:\\calculator\\" + dir);
}

std::vector<std::string> SDCardController::list_dir(std::string dir)
{
	dir = "C:\\calculator\\" + dir;
	std::vector<std::string> files;
	if (std::filesystem::exists(dir))
		for (const auto& entry : std::filesystem::directory_iterator(dir))
			files.push_back(entry.path().filename().string());
	return files;
}

#endif