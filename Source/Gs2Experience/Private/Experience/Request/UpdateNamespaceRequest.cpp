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

#include "Experience/Request/UpdateNamespaceRequest.h"

namespace Gs2::Experience::Request
{
    FUpdateNamespaceRequest::FUpdateNamespaceRequest():
        NamespaceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        TransactionSettingValue(nullptr),
        RankCapScriptIdValue(TOptional<FString>()),
        ChangeExperienceScriptValue(nullptr),
        ChangeRankScriptValue(nullptr),
        ChangeRankCapScriptValue(nullptr),
        OverflowExperienceScriptValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FUpdateNamespaceRequest::FUpdateNamespaceRequest(
        const FUpdateNamespaceRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
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

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithTransactionSetting(
        const TSharedPtr<Model::FTransactionSetting> TransactionSetting
    )
    {
        this->TransactionSettingValue = TransactionSetting;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithRankCapScriptId(
        const TOptional<FString> RankCapScriptId
    )
    {
        this->RankCapScriptIdValue = RankCapScriptId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithChangeExperienceScript(
        const TSharedPtr<Model::FScriptSetting> ChangeExperienceScript
    )
    {
        this->ChangeExperienceScriptValue = ChangeExperienceScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithChangeRankScript(
        const TSharedPtr<Model::FScriptSetting> ChangeRankScript
    )
    {
        this->ChangeRankScriptValue = ChangeRankScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithChangeRankCapScript(
        const TSharedPtr<Model::FScriptSetting> ChangeRankCapScript
    )
    {
        this->ChangeRankCapScriptValue = ChangeRankCapScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithOverflowExperienceScript(
        const TSharedPtr<Model::FScriptSetting> OverflowExperienceScript
    )
    {
        this->OverflowExperienceScriptValue = OverflowExperienceScript;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::WithLogSetting(
        const TSharedPtr<Model::FLogSetting> LogSetting
    )
    {
        this->LogSettingValue = LogSetting;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateNamespaceRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TSharedPtr<Model::FTransactionSetting> FUpdateNamespaceRequest::GetTransactionSetting() const
    {
        if (!TransactionSettingValue.IsValid())
        {
            return nullptr;
        }
        return TransactionSettingValue;
    }

    TOptional<FString> FUpdateNamespaceRequest::GetRankCapScriptId() const
    {
        return RankCapScriptIdValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetChangeExperienceScript() const
    {
        if (!ChangeExperienceScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeExperienceScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetChangeRankScript() const
    {
        if (!ChangeRankScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeRankScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetChangeRankCapScript() const
    {
        if (!ChangeRankCapScriptValue.IsValid())
        {
            return nullptr;
        }
        return ChangeRankCapScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FUpdateNamespaceRequest::GetOverflowExperienceScript() const
    {
        if (!OverflowExperienceScriptValue.IsValid())
        {
            return nullptr;
        }
        return OverflowExperienceScriptValue;
    }

    TSharedPtr<Model::FLogSetting> FUpdateNamespaceRequest::GetLogSetting() const
    {
        if (!LogSettingValue.IsValid())
        {
            return nullptr;
        }
        return LogSettingValue;
    }

    TSharedPtr<FUpdateNamespaceRequest> FUpdateNamespaceRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateNamespaceRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTransactionSetting(Data->HasField("transactionSetting") ? [Data]() -> Model::FTransactionSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("transactionSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FTransactionSetting::FromJson(Data->GetObjectField("transactionSetting"));
             }() : nullptr)
            ->WithRankCapScriptId(Data->HasField("rankCapScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("rankCapScriptId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithChangeExperienceScript(Data->HasField("changeExperienceScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("changeExperienceScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("changeExperienceScript"));
             }() : nullptr)
          ->WithChangeRankScript(Data->HasField("changeRankScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("changeRankScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("changeRankScript"));
             }() : nullptr)
          ->WithChangeRankCapScript(Data->HasField("changeRankCapScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("changeRankCapScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("changeRankCapScript"));
             }() : nullptr)
          ->WithOverflowExperienceScript(Data->HasField("overflowExperienceScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("overflowExperienceScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("overflowExperienceScript"));
             }() : nullptr)
          ->WithLogSetting(Data->HasField("logSetting") ? [Data]() -> Model::FLogSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("logSetting"))
                  {
                      return nullptr;
                  }
                  return Model::FLogSetting::FromJson(Data->GetObjectField("logSetting"));
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateNamespaceRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
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
        if (OverflowExperienceScriptValue != nullptr && OverflowExperienceScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("overflowExperienceScript", OverflowExperienceScriptValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}