object frmABLM: TfrmABLM
  Left = 306
  Top = 152
  Width = 398
  Height = 469
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'frmABLM'
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
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 281
    Height = 81
    Caption = 'Sequences: '
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 20
      Width = 61
      Height = 13
      Caption = 'Collection:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 48
      Top = 52
      Width = 30
      Height = 13
      Caption = 'Icon:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object cmbCollection: TComboBox
      Left = 80
      Top = 16
      Width = 193
      Height = 21
      ItemHeight = 13
      MaxLength = 8
      Sorted = True
      TabOrder = 0
      Text = 'no collection'
    end
    object Edit1: TEdit
      Left = 80
      Top = 48
      Width = 33
      Height = 21
      TabOrder = 1
      Text = '0'
    end
  end
  object btnSave: TButton
    Left = 304
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Save'
    Default = True
    TabOrder = 1
    OnClick = btnSaveClick
  end
  object btnCancel: TButton
    Left = 304
    Top = 40
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 2
    OnClick = btnCancelClick
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 96
    Width = 281
    Height = 73
    Caption = 'Projectile Groups: '
    TabOrder = 3
    object Label3: TLabel
      Left = 40
      Top = 20
      Width = 41
      Height = 13
      Caption = 'Usage:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 23
      Top = 44
      Width = 58
      Height = 13
      Caption = 'Projectile:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object cmbUseGroup: TComboBox
      Left = 88
      Top = 16
      Width = 185
      Height = 21
      ItemHeight = 13
      MaxLength = 8
      Sorted = True
      TabOrder = 0
      Text = 'no group'
    end
    object cmbProjGroup: TComboBox
      Left = 88
      Top = 40
      Width = 185
      Height = 21
      ItemHeight = 13
      MaxLength = 8
      Sorted = True
      TabOrder = 1
      Text = 'no group'
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 176
    Width = 281
    Height = 201
    Caption = 'Properties: '
    TabOrder = 4
    object Label5: TLabel
      Left = 16
      Top = 20
      Width = 87
      Height = 13
      Caption = 'Purchase Cost:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 40
      Top = 44
      Width = 62
      Height = 13
      Caption = 'Sync Cost:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label7: TLabel
      Left = 8
      Top = 84
      Width = 107
      Height = 13
      Caption = 'Minimum Distance:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label8: TLabel
      Left = 8
      Top = 108
      Width = 110
      Height = 13
      Caption = 'Maximum Distance:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label9: TLabel
      Left = 8
      Top = 156
      Width = 37
      Height = 13
      Caption = 'Delay:'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object edtBuyCost: TEdit
      Left = 104
      Top = 16
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object edtSyncCost: TEdit
      Left = 104
      Top = 40
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object edtMinDist: TEdit
      Left = 128
      Top = 80
      Width = 49
      Height = 21
      TabOrder = 2
      Text = '0'
    end
    object edtMaxDist: TEdit
      Left = 128
      Top = 104
      Width = 49
      Height = 21
      TabOrder = 3
      Text = '0'
    end
    object edtDelay: TEdit
      Left = 128
      Top = 152
      Width = 49
      Height = 21
      TabOrder = 4
      Text = '0'
    end
  end
end
