import QtQuick
import QtQuick.Controls

Grid
{
  id: root

  readonly property int fontPointSize:    14
  readonly property int textBoxWidth:     180
  readonly property int textBoxHeight:    50
  readonly property int internalSpacing:  5

  columns: 3
  columnSpacing: 50
     rowSpacing: 30

  Column
  {
    id: numOfRowsOption
    spacing: internalSpacing

    CustomTextField
    {
      placeholderText: "Rows: " + gameManager.numOfRows.toString()
      onAccepted: function()
      {
        gameManager.numOfRows = parseInt(text);
        clear();
      }
      height: textBoxHeight
      width:  textBoxWidth
    }
  }

  Column
  {
    id: numOfColsOption
    spacing: internalSpacing

    CustomTextField
    {
      placeholderText: "Columns: " + gameManager.numOfCols.toString()
      onAccepted:
      {
        gameManager.numOfCols = parseInt(text)
        clear();
      }
      height: textBoxHeight
      width:  textBoxWidth
    }
  }

  Column
  {
    id: squareSizeOption
    spacing: internalSpacing

    CustomTextField
    {
      placeholderText: "Square Size: " + gameManager.squareSize.toString()
      onAccepted:
      {
        gameManager.squareSize = parseInt(text)
        clear();
      }
      height: textBoxHeight
      width:  textBoxWidth
    }
  }

  Column
  {
    id: refreshPeriodOption
    spacing: internalSpacing

    CustomTextField
    {
      placeholderText: "Period: " + gameManager.timerPeriod.toString() + " ms"
      onAccepted:
      {
        gameManager.timerPeriod = parseInt(text)
        clear();
      }
      height: textBoxHeight
      width:  textBoxWidth
    }
  }

  Column
  {
    id: squareSpacingOption
    spacing: internalSpacing

    CustomTextField
    {
      placeholderText: "Spacing: " + gameManager.squareSpacing.toString() + " px"
      onAccepted:
      {
        gameManager.squareSpacing = parseInt(text)
        clear();
      }
      height: textBoxHeight
      width:  textBoxWidth
    }
  }

  Column
  {
    id: animationAllowedSelection
    spacing: internalSpacing

    CustomButton
    {
      id: animationAllowedButton

      readonly property string allowedString:     "Allowed"
      readonly property string disallowedString:  "Disallowed"
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
  }
} // Grid
