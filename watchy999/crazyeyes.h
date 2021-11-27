
void Watchy999::drawCrazyEyesWatchFace(){
  const uint16_t eye_radius   = 32;
  const uint16_t pupil_radius = 8;
  const uint16_t eye_distance = 6;
  const uint16_t offset       = 32;
  const uint16_t center_x     = 100;
  const uint16_t center_y     = 100;
  const uint16_t teeth_radius = 4;
  const uint16_t mouth_offset = 20;
  const uint16_t pupil_center_dist = eye_radius - pupil_radius - 4;
  const uint16_t black_color = darkMode?GxEPD_BLACK:GxEPD_WHITE;
  const uint16_t white_color = darkMode?GxEPD_WHITE:GxEPD_BLACK;
  display.fillScreen(black_color);
  // draw left eye (hours)
  uint16_t eye_center_x = center_x - eye_radius - eye_distance;
  uint16_t eye_center_y = center_y - offset;
  display.fillCircle(eye_center_x, eye_center_y, eye_radius, white_color);
  float angle = 2 * 3.14159 * ((currentTime.Hour % 12) + (currentTime.Minute / 60.)) / 12.;
  uint16_t pupil_center_x = eye_center_x + sin(angle) * pupil_center_dist;
  uint16_t pupil_center_y = eye_center_y - cos(angle) * pupil_center_dist;
  display.fillCircle(pupil_center_x, pupil_center_y, pupil_radius, black_color);
  display.fillCircle(pupil_center_x + 2, pupil_center_y - 2, 2, white_color);
  // draw right eye (minutes)
  eye_center_x = center_x + eye_radius + eye_distance;
  display.fillCircle(eye_center_x, eye_center_y, eye_radius, white_color);
  angle = 2 * 3.14159 / 60 * currentTime.Minute;
  pupil_center_x = eye_center_x + sin(angle) * pupil_center_dist;
  pupil_center_y = eye_center_y - cos(angle) * pupil_center_dist;
  display.fillCircle(pupil_center_x, pupil_center_y, pupil_radius, black_color);
  display.fillCircle(pupil_center_x + 2, pupil_center_y - 2, 2, white_color);
  // draw mouth (day in binary)
  const uint16_t width = 3 * eye_radius + eye_distance;
  for(int8_t tooth_id = 0; tooth_id < 5; tooth_id++) {
    display.fillRoundRect(
      100 - width / 2 + tooth_id * width / 5,
      eye_center_y + eye_radius + mouth_offset,
      width / 5,
      19,
      teeth_radius,
      (uint16_t)(currentTime.Day & (1 << (4 - tooth_id)) ? black_color : white_color));
    display.drawRoundRect(
      100 - width / 2 + tooth_id * width / 5,
      eye_center_y + eye_radius + mouth_offset,
      width / 5,
      19,
      teeth_radius,
      white_color);
  }
}
