object frmNewTag: TfrmNewTag
  Left = 362
  Top = 410
  Width = 416
  Height = 114
  Caption = 'New Tag'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 8
    Top = 60
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
  object Label1: TLabel
    Left = 40
    Top = 36
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
  object Label3: TLabel
    Left = 44
    Top = 12
    Width = 33
    Height = 13
    Caption = 'Type:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object edtTagType: TEdit
    Left = 80
    Top = 8
    Width = 57
    Height = 21
    CharCase = ecLowerCase
    MaxLength = 4
    TabOrder = 0
    Text = 'type'
  end
  object edtTagDesc: TEdit
    Left = 80
    Top = 56
    Width = 217
    Height = 21
    CharCase = ecLowerCase
    MaxLength = 255
    TabOrder = 2
    Text = 'edttagdesc'
  end
  object edtTagName: TEdit
    Left = 80
    Top = 32
    Width = 217
    Height = 21
    CharCase = ecLowerCase
    TabOrder = 1
    Text = 'edttagdesc'
  end
  object btnCreate: TButton
    Left = 312
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Create'
    Default = True
    TabOrder = 3
    OnClick = btnCreateClick
  end
  object btnCancel: TButton
    Left = 312
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = btnCancelClick
  end
end
