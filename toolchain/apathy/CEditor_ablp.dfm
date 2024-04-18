object frmABLP: TfrmABLP
  Left = 484
  Top = 264
  Width = 308
  Height = 327
  Caption = 'Physical Abilities'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object txtABLPSprites: TLabel
    Left = 16
    Top = 16
    Width = 101
    Height = 13
    Caption = 'Sprite Collection Tag:'
  end
  object txtABLPProjGroupCreate: TLabel
    Left = 16
    Top = 72
    Width = 179
    Height = 13
    Caption = 'Projectile Group (Created when used):'
  end
  object txtABLPAbilityCost: TLabel
    Left = 16
    Top = 192
    Width = 54
    Height = 13
    Caption = 'Ability Cost:'
  end
  object txtABLPIconID: TLabel
    Left = 200
    Top = 16
    Width = 90
    Height = 13
    Caption = 'Icon Sequence ID:'
  end
  object txtABLPAmmunition: TLabel
    Left = 16
    Top = 240
    Width = 57
    Height = 13
    Caption = 'Ammunition:'
  end
  object txtABLPProjGroupUse: TLabel
    Left = 16
    Top = 128
    Width = 208
    Height = 13
    Caption = 'Projectile Group(Ammunition or scavenging):'
  end
  object comboABLPident: TComboBox
    Left = 16
    Top = 32
    Width = 161
    Height = 21
    ItemHeight = 13
    TabOrder = 0
  end
  object comboABLPProjCreate: TComboBox
    Left = 16
    Top = 88
    Width = 209
    Height = 21
    ItemHeight = 13
    TabOrder = 1
  end
  object editABLPAbilityCost: TEdit
    Left = 16
    Top = 208
    Width = 57
    Height = 21
    TabOrder = 2
    Text = '0'
  end
  object spnABLPAbilityCost: TUpDown
    Left = 73
    Top = 208
    Width = 15
    Height = 21
    Associate = editABLPAbilityCost
    Min = 0
    Position = 0
    TabOrder = 3
    Wrap = False
  end
  object editABLPIconID: TEdit
    Left = 200
    Top = 32
    Width = 33
    Height = 21
    TabOrder = 4
    Text = '0'
  end
  object spnABLPIconID: TUpDown
    Left = 233
    Top = 32
    Width = 15
    Height = 21
    Associate = editABLPIconID
    Min = 0
    Position = 0
    TabOrder = 5
    Wrap = False
  end
  object editABLPAmmunition: TEdit
    Left = 16
    Top = 256
    Width = 57
    Height = 21
    TabOrder = 6
    Text = '0'
  end
  object spnABLPAmmunition: TUpDown
    Left = 73
    Top = 256
    Width = 15
    Height = 21
    Associate = editABLPAmmunition
    Min = 0
    Position = 0
    TabOrder = 7
    Wrap = False
  end
  object comboABLPProjUse: TComboBox
    Left = 16
    Top = 144
    Width = 209
    Height = 21
    ItemHeight = 13
    TabOrder = 8
  end
  object btnABLPApply: TButton
    Left = 208
    Top = 216
    Width = 75
    Height = 25
    Caption = '&Apply'
    TabOrder = 9
  end
  object btnABLPCancel: TButton
    Left = 208
    Top = 256
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Cancel'
    TabOrder = 10
    OnClick = btnABLPCancelClick
  end
end
