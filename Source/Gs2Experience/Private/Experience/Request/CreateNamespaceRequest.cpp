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
        ExperienceCapScriptIdValue(TOptional<FString>()),
        ChangeExperienceScriptValue(nullptr),
        ChangeRankScriptValue(nullptr),
        ChangeRankCapScriptValue(nullptr),
        OverflowExperienceScriptValue(nullptr),
        LogSettingValue(nullptr)
    {
    }

    FCreateNamespaceRequest::FCreateNamespaceRequest(
        const FCreateNamespaceRequest& From
    ):
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        ExperienceCapScriptIdValue(From.ExperienceCapScriptIdValue),
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

    TSharedPtr<FCreateNamespaceRequest> FCreateNamespaceRequest::WithExperienceCapScriptId(
        const TOptional<FString> ExperienceCapScriptId
    )
    {
        this->ExperienceCapScriptIdValue = ExperienceCapScriptId;
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
        const TSharedPtr<Model::FScriptSetting> OverflowExperienceScript
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

    TOptional<FString> FCreateNamespaceRequest::GetExperienceCapScriptId() const
    {
        return ExperienceCapScriptIdValue;
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

    TSharedPtr<Model::FScriptSetting> FCreateNamespaceRequest::GetOverflowExperienceScript() const
    {
        if (!OverflowExperienceScriptValue.IsValid())
        {
            return nullptr;
        }
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
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("name", v))
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
            ->WithExperienceCapScriptId(Data->HasField("experienceCapScriptId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("experienceCapScriptId", v))
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
        if (ExperienceCapScriptIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceCapScriptId", ExperienceCapScriptIdValue.GetValue());
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