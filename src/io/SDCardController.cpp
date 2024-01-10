#include "io/SDCardController.h"
#ifdef PICO

bool SDCardController::save_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes)
{
	if (!ready() || !set_directory(dir)) return false;
	FIL file;
	FRESULT fr = f_open(&file, filename.c_str(), FA_WRITE | FA_CREATE_ALWAYS);
	if (FR_OK != fr) {
		std::cout << "f_open error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		return false;
	}

	UINT bytes_written;
	fr = f_write(&file, bytes->data(), bytes->size(), &bytes_written);

	if (bytes_written == bytes->size()) return true;

	std::cout << "f_write error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
	return false;
}

bool SDCardController::read_file(std::string dir, std::string filename, std::vector<uint8_t>* bytes)
{
	if (!ready() || !set_directory(dir)) return false;
	return false;
}

void SDCardController::init()
{
	_sd_card = &sd_card;

	if (_sd_card->use_card_detect) {
		// Set up an interrupt on Card Detect to detect removal of the card when it happens:
		gpio_set_irq_enabled_with_callback(
			_sd_card->card_detect_gpio,
			GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
			true,
			&card_detect_callback);
	}

	if (sd_card_detect(_sd_card)) {
		FRESULT fr = f_mount(&_sd_card->fatfs, _sd_card->pcName, 1);
		if (FR_OK != fr) std::cout << "f_mount error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		else std::cout << "Mounted " << _sd_card->pcName << std::endl;
		fr = f_chdrive(_sd_card->pcName);
		if (FR_OK != fr) std::cout << "f_chdrive error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
		else std::cout << "Changed drive to " << _sd_card->pcName << std::endl;
	}
}

bool SDCardController::set_directory(std::string dir)
{
	FRESULT fr = f_stat(("/" + dir).c_str(), NULL);

	if (fr != FR_OK) {
		f_chdir("/");
		f_mkdir(dir.c_str());
	}

	fr = f_chdir(("/" + dir).c_str());

	if (fr == FR_OK) return true;
	return false;
}

bool SDCardController::ready()
{
	return _sd_card->mounted;
}

void SDCardController::card_detect_callback(uint gpio, uint32_t events)
{
	static bool busy;
	if (busy) return; // Avoid switch bounce
	busy = true;
	if (_sd_card->card_detect_gpio == gpio) {
		if (_sd_card->mounted) {
			std::cout << "Card Detect Interrupt: unmounting " << _sd_card->pcName << std::endl;
			FRESULT fr = f_unmount(_sd_card->pcName);
			if (FR_OK == fr) {
				_sd_card->mounted = false;
			} else {
				std::cout << "f_unmount error: " << FRESULT_str(fr) << " (" << fr << ")" << std::endl;
			}
		}
		_sd_card->m_Status |= STA_NOINIT; // in case medium is removed
		sd_card_detect(_sd_card);
	}
	busy = false;
}

#endif