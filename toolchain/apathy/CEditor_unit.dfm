object frmUNIT: TfrmUNIT
  Left = 338
  Top = 352
  Width = 389
  Height = 172
  Caption = 'frmUNIT'
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
  object Label2: TLabel
    Left = 34
    Top = 12
    Width = 36
    Height = 13
    Caption = 'Mech:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 10
    Top = 36
    Width = 60
    Height = 13
    Caption = 'Character:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label4: TLabel
    Left = 32
    Top = 60
    Width = 38
    Height = 13
    Caption = 'Script:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label1: TLabel
    Left = 29
    Top = 94
    Width = 43
    Height = 13
    Caption = 'Names:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label5: TLabel
    Left = 32
    Top = 116
    Width = 40
    Height = 13
    Caption = 'Flavor:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object btnSave: TButton
    Left = 296
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Save'
    Default = True
    TabOrder = 0
    OnClick = btnSaveClick
  end
  object btnCancel: TButton
    Left = 296
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 1
    OnClick = btnCancelClick
  end
  object cmbMechTag: TComboBox
    Left = 72
    Top = 8
    Width = 193
    Height = 21
    ItemHeight = 13
    TabOrder = 2
  end
  object cmbCharTag: TComboBox
    Left = 72
    Top = 32
    Width = 193
    Height = 21
    ItemHeight = 13
    TabOrder = 3
  end
  object cmbScriTag: TComboBox
    Left = 72
    Top = 56
    Width = 193
    Height = 21
    ItemHeight = 13
    TabOrder = 4
  end
  object cmbNames: TComboBox
    Left = 72
    Top = 88
    Width = 193
    Height = 21
    ItemHeight = 13
    TabOrder = 5
  end
  object cmbFlavor: TComboBox
    Left = 72
    Top = 112
    Width = 193
    Height = 21
    ItemHeight = 13
    TabOrder = 6
  end
end
