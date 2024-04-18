object frmSTRC: TfrmSTRC
  Left = 406
  Top = 318
  Width = 559
  Height = 530
  Caption = 'frmSTRC'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object txtStrings: TMemo
    Left = 8
    Top = 40
    Width = 537
    Height = 457
    Lines.Strings = (
      '')
    TabOrder = 0
  end
  object btnSave: TButton
    Left = 376
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Save'
    Default = True
    TabOrder = 1
    OnClick = btnSaveClick
  end
  object btnCancel: TButton
    Left = 464
    Top = 8
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
end
