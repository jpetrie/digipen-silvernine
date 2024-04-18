object frmTagProps: TfrmTagProps
  Left = 326
  Top = 369
  Width = 405
  Height = 124
  ActiveControl = edtTagName
  Caption = 'Tag Properties'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 40
    Top = 12
    Width = 37
    Height = 13
    Caption = 'Name:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 8
    Top = 36
    Width = 69
    Height = 13
    Caption = 'Description:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label3: TLabel
    Left = 24
    Top = 64
    Width = 53
    Height = 13
    Caption = 'File Size:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object edtTagName: TEdit
    Left = 80
    Top = 8
    Width = 217
    Height = 21
    CharCase = ecLowerCase
    MaxLength = 8
    TabOrder = 0
    Text = 'edttagname'
  end
  object edtTagDesc: TEdit
    Left = 80
    Top = 32
    Width = 217
    Height = 21
    CharCase = ecLowerCase
    MaxLength = 255
    TabOrder = 1
    Text = 'edttagdesc'
  end
  object txtFileSize: TStaticText
    Left = 80
    Top = 64
    Width = 10
    Height = 17
    Caption = '0'
    TabOrder = 4
  end
  object btnSave: TButton
    Left = 312
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Save'
    Default = True
    TabOrder = 2
    OnClick = btnSaveClick
  end
  object btnCancel: TButton
    Left = 312
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = btnCancelClick
  end
end
