DS1302 rtc(RTC_RST, RTC_IO, RTC_CLK);

void rtc_setup() {
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
}

int rtc_read(int h_or_m) {
  Time t = rtc.time();

  if (h_or_m == 0) {
    return t.hr;
  }
  else {
    return t.min;
  }
}

