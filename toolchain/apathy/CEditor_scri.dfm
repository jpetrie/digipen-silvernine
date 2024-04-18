object frmSCRI: TfrmSCRI
  Left = 190
  Top = 180
  Width = 696
  Height = 480
  Caption = 'frmSCRI'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Visible = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object edtScript: TMemo
    Left = 8
    Top = 48
    Width = 673
    Height = 393
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'ProFontWindows'
    Font.Style = []
    Lines.Strings = (
      'edtScript')
    ParentFont = False
    TabOrder = 0
    WantTabs = True
  end
  object btnSave: TButton
    Left = 496
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 1
    OnClick = btnSaveClick
  end
  object btnCancel: TButton
    Left = 592
    Top = 16
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 2
  end
end
