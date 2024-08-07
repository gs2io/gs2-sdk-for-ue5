/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Experience/Request/CreateNamespaceRequest.h"

namespace Gs2::Experience::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        RankCapScriptIdValue(TOptional<FString>()),
        ChangeExperienceScriptValue(nullptr),
        ChangeRankScriptValue(nullptr),
        ChangeRankCapScriptValue(nullptr),
        OverflowExperienceScriptValue(TOptional<FString>()),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        TransactionSettingValue(From.TransactionSettingValue),
        RankCapScriptIdValue(From.RankCapScriptIdValue),
        ChangeExperienceScriptValue(From.ChangeExperienceScriptValue),
        ChangeRankScriptValue(From.ChangeRankScriptValue),
        ChangeRankCapScriptValue(From.ChangeRankCapScriptValue),
        OverflowExperienceScriptValue(From.OverflowExperienceScriptValue),
        LogSettingValue(From.LogSettingValue)
    {
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithRankCapScriptId(
        const TOptional<FString> RankCapScriptId
    )
    {
        this->RankCapScriptIdValue = RankCapScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangeExperienceScript(
        const TSharedPtr<Model::FScriptSetting> ChangeExperienceScript
    )
    {
        this->ChangeExperienceScriptValue = ChangeExperienceScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangeRankScript(
        const TSharedPtr<Model::FScriptSetting> ChangeRankScript
    )
    {
        this->ChangeRankScriptValue = ChangeRankScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithChangeRankCapScript(
        const TSharedPtr<Model::FScriptSetting> ChangeRankCapScript
    )
    {
        this->ChangeRankCapScriptValue = ChangeRankCapScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithOverflowExperienceScript(
        const TOptional<FString> OverflowExperienceScript
    )
    {
        this->OverflowExperienceScriptValue = OverflowExperienceScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithLogSetting(
        const TSharedPtr<Model::FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TOptional<FString> FCreateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TSharedPtr<Model::FTransactionSetting> FCreateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetRankCapScriptId() const
    {
        return RankCapScriptIdValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetChangeExperienceScript() const
    {
        if (!ChangeExperienceScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeExperienceScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetChangeRankScript() const
    {
        if (!ChangeRankScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeRankScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetChangeRankCapScript() const
    {
        if (!ChangeRankCapScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeRankCapScriptValue;
    }

    TOptional<FString> FCreateNamespaceRequest::GetOverflowExperienceScript() const
    {
        return OverflowExperienceScriptValue;
    }

    TSharedPtr<Model::FLogSetting> FCreateNamespaceRequest::GetLogSetting() const
    {
        if (!LogSettingValue.IsValid())
        {
            return nullptr;
        }
        return LogSettingValue;
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateNamespaceRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTransactionSetting(Data->HasField(ANSI_TO_TCHAR("transactionSetting")) ? [Data]() -> Model::FTransactionSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("transactionSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FTransactionSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("transactionSetting")));
              }() : nullptr)
            ->WithRankCapScriptId(Data->HasField(ANSI_TO_TCHAR("rankCapScriptId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("rankCapScriptId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithChangeExperienceScript(Data->HasField(ANSI_TO_TCHAR("changeExperienceScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeExperienceScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeExperienceScript")));
              }() : nullptr)
          ->WithChangeRankScript(Data->HasField(ANSI_TO_TCHAR("changeRankScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeRankScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeRankScript")));
              }() : nullptr)
          ->WithChangeRankCapScript(Data->HasField(ANSI_TO_TCHAR("changeRankCapScript")) ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("changeRankCapScript")))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("changeRankCapScript")));
              }() : nullptr)
            ->WithOverflowExperienceScript(Data->HasField(ANSI_TO_TCHAR("overflowExperienceScript")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("overflowExperienceScript"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithLogSetting(Data->HasField(ANSI_TO_TCHAR("logSetting")) ? [Data]() -> Model::FLogSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("logSetting")))
                  {
                      return nullptr;
                  }
                  return Model::FLogSetting::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("logSetting")));
              }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (TransactionSettingValue != nullptr && TransactionSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("transactionSetting", TransactionSettingValue->ToJson());
        }
        if (RankCapScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("rankCapScriptId", RankCapScriptIdValue.GetValue());
        }
        if (ChangeExperienceScriptValue != nullptr && ChangeExperienceScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeExperienceScript", ChangeExperienceScriptValue->ToJson());
        }
        if (ChangeRankScriptValue != nullptr && ChangeRankScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeRankScript", ChangeRankScriptValue->ToJson());
        }
        if (ChangeRankCapScriptValue != nullptr && ChangeRankCapScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("changeRankCapScript", ChangeRankCapScriptValue->ToJson());
        }
        if (OverflowExperienceScriptValue.IsSet())
        {
            JsonRootObject->SetStringField("overflowExperienceScript", OverflowExperienceScriptValue.GetValue());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}