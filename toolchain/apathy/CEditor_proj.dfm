object frmPROJ: TfrmPROJ
  Left = 429
  Top = 51
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Projectile Editor'
  ClientHeight = 377
  ClientWidth = 515
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
  object cmbPROJobje_tag: TComboBox
    Left = 8
    Top = 8
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    Text = 'OBJE tag'
  end
  object cmbPROJsprc_tag: TComboBox
    Left = 168
    Top = 8
    Width = 145
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = 'SPRC tag'
  end
  object grpPROJSequences: TGroupBox
    Left = 8
    Top = 232
    Width = 281
    Height = 129
    Caption = 'Sequences'
    TabOrder = 2
    object lblPROJInFlightSeqIdx: TLabel
      Left = 17
      Top = 27
      Width = 144
      Height = 13
      Caption = 'In-flight Sequence Index:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPROJAtRestSeqIdx: TLabel
      Left = 17
      Top = 59
      Width = 138
      Height = 13
      Caption = 'At-rest Sequence Index:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPROJDetonationSeqIdx: TLabel
      Left = 17
      Top = 91
      Width = 163
      Height = 13
      Caption = 'Detonation Sequence Index:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object editPROJInFlightSeqIdx: TEdit
      Left = 200
      Top = 24
      Width = 33
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object editPROJAtRestSeqIdx: TEdit
      Left = 200
      Top = 56
      Width = 33
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object editPROJDetonationSeqIdx: TEdit
      Left = 200
      Top = 88
      Width = 33
      Height = 21
      TabOrder = 2
      Text = '0'
    end
  end
  object grpPROJDamageAttributes: TGroupBox
    Left = 8
    Top = 40
    Width = 281
    Height = 177
    Caption = 'Damage Attributes'
    TabOrder = 3
    object lblPROJDamage: TLabel
      Left = 24
      Top = 104
      Width = 51
      Height = 13
      Caption = 'Damage:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPROJDamageRadius: TLabel
      Left = 24
      Top = 136
      Width = 94
      Height = 13
      Caption = 'Damage Radius:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPROJDamageRadiusFillRate: TLabel
      Left = 24
      Top = 64
      Width = 145
      Height = 13
      Caption = 'Damage Radius Fill Rate:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblPROJDamageType: TLabel
      Left = 24
      Top = 24
      Width = 83
      Height = 13
      Caption = 'Damage Type:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object editPROJDamageMin: TEdit
      Left = 128
      Top = 104
      Width = 57
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object editPROJDamageMax: TEdit
      Left = 208
      Top = 104
      Width = 57
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object editPROJDamageRadiusMin: TEdit
      Left = 128
      Top = 136
      Width = 57
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object editPROJDamageRadiusMax: TEdit
      Left = 208
      Top = 136
      Width = 57
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object editPROJDamageFillRate: TEdit
      Left = 216
      Top = 64
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '0'
    end
    object cmbPROJDamageType: TComboBox
      Left = 120
      Top = 24
      Width = 145
      Height = 21
      ItemHeight = 13
      TabOrder = 5
      Text = 'cmbPROJDamageType'
    end
  end
  object grpPROJFlags: TGroupBox
    Left = 304
    Top = 40
    Width = 193
    Height = 177
    Caption = 'Flags'
    TabOrder = 4
    object chkPROJPromotes: TCheckBox
      Left = 16
      Top = 24
      Width = 153
      Height = 25
      Caption = 'Promotes on Detonation'
      TabOrder = 0
    end
    object chkPROJDetonateCollision: TCheckBox
      Left = 16
      Top = 49
      Width = 137
      Height = 17
      Caption = 'Detonates on Collision'
      TabOrder = 1
    end
    object chkPROJDetonateRest: TCheckBox
      Left = 16
      Top = 72
      Width = 137
      Height = 17
      Caption = 'Detonates at Rest'
      TabOrder = 2
    end
    object chkPROJDetonateExplosives: TCheckBox
      Left = 16
      Top = 96
      Width = 129
      Height = 17
      Caption = 'Detonates Explosives'
      TabOrder = 3
    end
    object chkPROJIgnoreShielding: TCheckBox
      Left = 16
      Top = 120
      Width = 137
      Height = 17
      Caption = 'Ignores Shielding'
      TabOrder = 4
    end
    object chkPROJIgnoreOwner: TCheckBox
      Left = 16
      Top = 144
      Width = 97
      Height = 17
      Caption = 'Ignores Owner'
      TabOrder = 5
    end
  end
  object btnPROJApply: TButton
    Left = 416
    Top = 240
    Width = 75
    Height = 25
    Caption = 'Apply'
    TabOrder = 5
    OnClick = btnPROJApplyClick
  end
  object btnPROJRevert: TButton
    Left = 416
    Top = 288
    Width = 75
    Height = 25
    Caption = 'Revert'
    TabOrder = 6
    OnClick = btnPROJRevertClick
  end
  object btnPROJCancel: TButton
    Left = 416
    Top = 336
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 7
    OnClick = btnPROJCancelClick
  end
  object txtPROJDamageRange: TStaticText
    Left = 196
    Top = 145
    Width = 13
    Height = 17
    Caption = 'to'
    TabOrder = 8
  end
  object txtPROJDamageRadius: TStaticText
    Left = 196
    Top = 177
    Width = 13
    Height = 17
    Caption = 'to'
    TabOrder = 9
  end
end
