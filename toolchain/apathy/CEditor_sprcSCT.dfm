object frmSPRCCollectionTitle: TfrmSPRCCollectionTitle
  Left = 944
  Top = 806
  Width = 294
  Height = 120
  BorderIcons = [biSystemMenu]
  Caption = 'Sprite Collection Title'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poOwnerFormCenter
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object txtSPRCCollectionTitle: TLabel
    Left = 8
    Top = 8
    Width = 72
    Height = 13
    Caption = 'Collection Title:'
  end
  object btnSPRCCollectionOK: TButton
    Left = 8
    Top = 56
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = btnSPRCCollectionOKClick
  end
  object btnSPRCCollectionCancel: TButton
    Left = 96
    Top = 56
    Width = 75
    Height = 25
    Caption = '&Cancel'
    TabOrder = 1
    OnClick = btnSPRCCollectionCancelClick
  end
  object editSPRCSpriteCollectionTitle: TEdit
    Left = 8
    Top = 24
    Width = 265
    Height = 21
    TabOrder = 2
    OnKeyDown = editSPRCSpriteCollectionTitleKeyDown
  end
end
