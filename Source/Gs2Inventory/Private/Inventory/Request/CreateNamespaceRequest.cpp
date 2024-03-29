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

#include "Inventory/Request/CreateNamespaceRequest.h"

namespace Gs2::Inventory::Request
{
    FCreateNamespaceRequest::FCreateNamespaceRequest():
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        AcquireScriptValue(nullptr),
        OverflowScriptValue(nullptr),
        ConsumeScriptValue(nullptr),
        SimpleItemAcquireScriptValue(nullptr),
        SimpleItemConsumeScriptValue(nullptr),
        BigItemAcquireScriptValue(nullptr),
        BigItemConsumeScriptValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        AcquireScriptValue(From.AcquireScriptValue),
        OverflowScriptValue(From.OverflowScriptValue),
        ConsumeScriptValue(From.ConsumeScriptValue),
        SimpleItemAcquireScriptValue(From.SimpleItemAcquireScriptValue),
        SimpleItemConsumeScriptValue(From.SimpleItemConsumeScriptValue),
        BigItemAcquireScriptValue(From.BigItemAcquireScriptValue),
        BigItemConsumeScriptValue(From.BigItemConsumeScriptValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithAcquireScript(
        const TSharedPtr<Model::FScriptSetting> AcquireScript
    )
    {
        this->AcquireScriptValue = AcquireScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithOverflowScript(
        const TSharedPtr<Model::FScriptSetting> OverflowScript
    )
    {
        this->OverflowScriptValue = OverflowScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithConsumeScript(
        const TSharedPtr<Model::FScriptSetting> ConsumeScript
    )
    {
        this->ConsumeScriptValue = ConsumeScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithSimpleItemAcquireScript(
        const TSharedPtr<Model::FScriptSetting> SimpleItemAcquireScript
    )
    {
        this->SimpleItemAcquireScriptValue = SimpleItemAcquireScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithSimpleItemConsumeScript(
        const TSharedPtr<Model::FScriptSetting> SimpleItemConsumeScript
    )
    {
        this->SimpleItemConsumeScriptValue = SimpleItemConsumeScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithBigItemAcquireScript(
        const TSharedPtr<Model::FScriptSetting> BigItemAcquireScript
    )
    {
        this->BigItemAcquireScriptValue = BigItemAcquireScript;
        return SharedThis(this);
    }

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithBigItemConsumeScript(
        const TSharedPtr<Model::FScriptSetting> BigItemConsumeScript
    )
    {
        this->BigItemConsumeScriptValue = BigItemConsumeScript;
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

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetAcquireScript() const
    {
        if (!AcquireScriptValue.IsValid())
        {
            return nullptr;
        }
        return AcquireScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetOverflowScript() const
    {
        if (!OverflowScriptValue.IsValid())
        {
            return nullptr;
        }
        return OverflowScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetConsumeScript() const
    {
        if (!ConsumeScriptValue.IsValid())
        {
            return nullptr;
        }
        return ConsumeScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetSimpleItemAcquireScript() const
    {
        if (!SimpleItemAcquireScriptValue.IsValid())
        {
            return nullptr;
        }
        return SimpleItemAcquireScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetSimpleItemConsumeScript() const
    {
        if (!SimpleItemConsumeScriptValue.IsValid())
        {
            return nullptr;
        }
        return SimpleItemConsumeScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetBigItemAcquireScript() const
    {
        if (!BigItemAcquireScriptValue.IsValid())
        {
            return nullptr;
        }
        return BigItemAcquireScriptValue;
    }

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetBigItemConsumeScript() const
    {
        if (!BigItemConsumeScriptValue.IsValid())
        {
            return nullptr;
        }
        return BigItemConsumeScriptValue;
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
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("name", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDescription(Data->HasField("description") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("description", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAcquireScript(Data->HasField("acquireScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("acquireScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("acquireScript"));
              }() : nullptr)
          ->WithOverflowScript(Data->HasField("overflowScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("overflowScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("overflowScript"));
              }() : nullptr)
          ->WithConsumeScript(Data->HasField("consumeScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("consumeScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("consumeScript"));
              }() : nullptr)
          ->WithSimpleItemAcquireScript(Data->HasField("simpleItemAcquireScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("simpleItemAcquireScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("simpleItemAcquireScript"));
              }() : nullptr)
          ->WithSimpleItemConsumeScript(Data->HasField("simpleItemConsumeScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("simpleItemConsumeScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("simpleItemConsumeScript"));
              }() : nullptr)
          ->WithBigItemAcquireScript(Data->HasField("bigItemAcquireScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("bigItemAcquireScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("bigItemAcquireScript"));
              }() : nullptr)
          ->WithBigItemConsumeScript(Data->HasField("bigItemConsumeScript") ? [Data]() -> Model::FScriptSettingPtr
              {
                  if (Data->HasTypedField<EJson::Null>("bigItemConsumeScript"))
                  {
                      return nullptr;
                  }
                  return Model::FScriptSetting::FromJson(Data->GetObjectField("bigItemConsumeScript"));
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
        if (AcquireScriptValue != nullptr && AcquireScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("acquireScript", AcquireScriptValue->ToJson());
        }
        if (OverflowScriptValue != nullptr && OverflowScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("overflowScript", OverflowScriptValue->ToJson());
        }
        if (ConsumeScriptValue != nullptr && ConsumeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("consumeScript", ConsumeScriptValue->ToJson());
        }
        if (SimpleItemAcquireScriptValue != nullptr && SimpleItemAcquireScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("simpleItemAcquireScript", SimpleItemAcquireScriptValue->ToJson());
        }
        if (SimpleItemConsumeScriptValue != nullptr && SimpleItemConsumeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("simpleItemConsumeScript", SimpleItemConsumeScriptValue->ToJson());
        }
        if (BigItemAcquireScriptValue != nullptr && BigItemAcquireScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("bigItemAcquireScript", BigItemAcquireScriptValue->ToJson());
        }
        if (BigItemConsumeScriptValue != nullptr && BigItemConsumeScriptValue.IsValid())
        {
            JsonRootObject->SetObjectField("bigItemConsumeScript", BigItemConsumeScriptValue->ToJson());
        }
        if (LogSettingValue != nullptr && LogSettingValue.IsValid())
        {
            JsonRootObject->SetObjectField("logSetting", LogSettingValue->ToJson());
        }
        return JsonRootObject;
    }
}