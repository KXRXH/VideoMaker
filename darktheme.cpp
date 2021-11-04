#include "darktheme.h"

QPalette darktheme::getDarkTheme() {
  // Setting colors
  const QColor darkGray(43, 43, 43);
  const QColor gray(128, 128, 128);
  const QColor black(25, 25, 25);
  const QColor blue(42, 130, 218);
  //-------------------------------------------------------------------------------------------------------//
  // Setting a dark theme
  QPalette DARK_PALETTE;
  DARK_PALETTE.setColor(QPalette::Window, darkGray);
  DARK_PALETTE.setColor(QPalette::WindowText, Qt::white);
  DARK_PALETTE.setColor(QPalette::Base, black);
  DARK_PALETTE.setColor(QPalette::AlternateBase, darkGray);
  DARK_PALETTE.setColor(QPalette::ToolTipBase, blue);
  DARK_PALETTE.setColor(QPalette::ToolTipText, Qt::white);
  DARK_PALETTE.setColor(QPalette::Text, Qt::white);
  DARK_PALETTE.setColor(QPalette::Button, darkGray);
  DARK_PALETTE.setColor(QPalette::ButtonText, Qt::white);
  DARK_PALETTE.setColor(QPalette::Link, blue);
  DARK_PALETTE.setColor(QPalette::Highlight, black);
  DARK_PALETTE.setColor(QPalette::HighlightedText, Qt::white);
  DARK_PALETTE.setColor(QPalette::Active, QPalette::Button, gray.darker());
  DARK_PALETTE.setColor(QPalette::Disabled, QPalette::ButtonText, gray);
  DARK_PALETTE.setColor(QPalette::Disabled, QPalette::WindowText, gray);
  DARK_PALETTE.setColor(QPalette::Disabled, QPalette::Text, gray);
  DARK_PALETTE.setColor(QPalette::Disabled, QPalette::Light, darkGray);
  return DARK_PALETTE;
}
