/**
  Instantiated by the `WelcomeScreen`. Contains the buttons and text boxes to set up the game options.
*/

// TODO: Consider adding a checkmark or changing the text to green colour when a value is accepted in the Options screen.

import QtQuick
import QtQuick.Controls

Grid
{
  readonly property int fontPointSize:    14
  readonly property int textBoxWidth:     180
  readonly property int textBoxHeight:    50

  columns: 3
  columnSpacing: 50
     rowSpacing: 30

  CustomTextField
  {
    height: textBoxHeight
    width:  textBoxWidth
    validator: IntValidator{ bottom: gameManager.minNumOfRowsAndCols; top: gameManager.maxNumOfRowsAndCols; }
    placeholderText: "Rows: " + gameManager.numOfRows.toString()
    onEditingFinished: function()
    {
      let parsedNumber = parseInt(text);
      if (Number.isNaN(parsedNumber))
      {;} // Avoids overwriting the previous value with an illegal value (for example, has the user clicked elsewhere without entering any input?)
      else
      {
        gameManager.numOfRows = parsedNumber;
        clear();
      }
    }
  }

  CustomTextField
  {
    height: textBoxHeight
    width:  textBoxWidth
    validator: IntValidator{ bottom: gameManager.minNumOfRowsAndCols; top: gameManager.maxNumOfRowsAndCols; }
    placeholderText: "Columns: " + gameManager.numOfCols.toString()
    onEditingFinished: function()
    {
      let parsedNumber = parseInt(text);
      if (Number.isNaN(parsedNumber))
      {;} // Avoids overwriting the previous value with an illegal value (for example, has the user clicked elsewhere without entering any input?)
      else
      {
        gameManager.numOfCols = parseInt(text);
        clear();
      }
    }
  }

  CustomTextField
  {
    height: textBoxHeight
    width:  textBoxWidth
    validator: IntValidator{ bottom: gameManager.minSquareSize; top: gameManager.maxSquareSize; }
    placeholderText: "Square Size: " + gameManager.squareSize.toString()
    onEditingFinished: function()
    {
      let parsedNumber = parseInt(text);
      if (Number.isNaN(parsedNumber))
      {;} // Avoids overwriting the previous value with an illegal value (for example, has the user clicked elsewhere without entering any input?)
      else
      {
        gameManager.squareSize = parseInt(text);
        clear();
      }
    }
  }

  CustomTextField
  {
    height: textBoxHeight
    width:  textBoxWidth
    validator: IntValidator{ bottom: gameManager.minTimerPeriod_ms; top: gameManager.maxTimerPeriod_ms; }
    placeholderText: "Period: " + gameManager.timerPeriod.toString() + " ms"
    onEditingFinished: function()
    {
      let parsedNumber = parseInt(text);
      if (Number.isNaN(parsedNumber))
      {;} // Avoids overwriting the previous value with an illegal value (for example, has the user clicked elsewhere without entering any input?)
      else
      {
        gameManager.timerPeriod = parseInt(text);
        clear();
      }
    }
  }

  CustomTextField
  {
    height: textBoxHeight
    width:  textBoxWidth
    validator: IntValidator{ bottom: gameManager.minSquareSpacing; top: gameManager.maxSquareSpacing; }
    placeholderText: "Spacing: " + gameManager.squareSpacing.toString() + " px"
    onEditingFinished: function()
    {
      let parsedNumber = parseInt(text);
      if (Number.isNaN(parsedNumber))
      {;} // Avoids overwriting the previous value with an illegal value (for example, has the user clicked elsewhere without entering any input?)
      else
      {
        gameManager.squareSpacing = parseInt(text);
        clear();
      }
    }
  }

  CustomButton
  {
    readonly property string allowedString:     "Anim. Allowed"
    readonly property string disallowedString:  "Anim. Disallowed"
    readonly property string white:             "white"
    readonly property string black:             "black"
    readonly property string normalGreen:       "#007F00"
    readonly property string pushedGreen:       "#00AF00"
    readonly property string hoverGreen:        "#00FF00"
    readonly property string normalOrange:      "#ff8800"
    readonly property string pushedOrange:      "#ffaa00"
    readonly property string hoverOrange:       "#ffcc00"

    width:  textBoxWidth
    height: textBoxHeight
    text_a: gameManager.isAnimationAllowed ? allowedString : disallowedString
    pointSize_a: fontPointSize

    normalTextColour_a: gameManager.isAnimationAllowed ? white       : black
    hoverTextColour_a:  gameManager.isAnimationAllowed ? white       : black
    hoverColour_a:      gameManager.isAnimationAllowed ? normalGreen : normalOrange
    normalColour_a:     gameManager.isAnimationAllowed ? pushedGreen : pushedOrange
    pushedColour_a:     gameManager.isAnimationAllowed ? hoverGreen  : hoverOrange

    ToolTip.visible:  hovered
    ToolTip.delay:    200
    ToolTip.text:     "Enable or disable the on / off animation on the game cells"

    onClicked:
    {
      gameManager.isAnimationAllowed = !gameManager.isAnimationAllowed;

      if (gameManager.isAnimationAllowed)
      {
        text_a = allowedString
        hoverColour_a       = normalGreen
        normalColour_a      = pushedGreen
        pushedColour_a      = hoverGreen
        normalTextColour_a  = white
        hoverTextColour_a   = white
      }
      else
      {
        text_a = disallowedString
        hoverColour_a  = normalOrange
        normalColour_a = pushedOrange
        pushedColour_a = hoverOrange
        normalTextColour_a  = black
        hoverTextColour_a   = black
      }
    }
  }
} // Grid
