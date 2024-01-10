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

#include "Stamina/Request/UpdateRecoverValueTableMasterRequest.h"

namespace Gs2::Stamina::Request
{
    FUpdateRecoverValueTableMasterRequest::FUpdateRecoverValueTableMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RecoverValueTableNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        ExperienceModelIdValue(TOptional<FString>()),
        ValuesValue(nullptr)
    {
    }

    FUpdateRecoverValueTableMasterRequest::FUpdateRecoverValueTableMasterRequest(
        const FUpdateRecoverValueTableMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RecoverValueTableNameValue(From.RecoverValueTableNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        ValuesValue(From.ValuesValue)
    {
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::WithRecoverValueTableName(
        const TOptional<FString> RecoverValueTableName
    )
    {
        this->RecoverValueTableNameValue = RecoverValueTableName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::WithValues(
        const TSharedPtr<TArray<int32>> Values
    )
    {
        this->ValuesValue = Values;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateRecoverValueTableMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateRecoverValueTableMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateRecoverValueTableMasterRequest::GetRecoverValueTableName() const
    {
        return RecoverValueTableNameValue;
    }

    TOptional<FString> FUpdateRecoverValueTableMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateRecoverValueTableMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateRecoverValueTableMasterRequest::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }

    TSharedPtr<TArray<int32>> FUpdateRecoverValueTableMasterRequest::GetValues() const
    {
        if (!ValuesValue.IsValid())
        {
            return nullptr;
        }
        return ValuesValue;
    }

    TSharedPtr<FUpdateRecoverValueTableMasterRequest> FUpdateRecoverValueTableMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateRecoverValueTableMasterRequest>()
            ->WithContextStack(Data->HasField("contextStack") ? TOptional<FString>(Data->GetStringField("contextStack")) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithRecoverValueTableName(Data->HasField("recoverValueTableName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("recoverValueTableName", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("experienceModelId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithValues(Data->HasField("values") ? [Data]() -> TSharedPtr<TArray<int32>>
              {
                  auto v = MakeShared<TArray<int32>>();
                  if (!Data->HasTypedField<EJson::Null>("values") && Data->HasTypedField<EJson::Array>("values"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("values"))
                      {
                          v->Add(JsonObjectValue->AsNumber());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<int32>>());
    }

    TSharedPtr<FJsonObject> FUpdateRecoverValueTableMasterRequest::ToJson() const
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
        if (RecoverValueTableNameValue.IsSet())
        {
            JsonRootObject->SetStringField("recoverValueTableName", RecoverValueTableNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (ValuesValue != nullptr && ValuesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ValuesValue)
            {
                v.Add(MakeShared<FJsonValueNumber>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("values", v);
        }
        return JsonRootObject;
    }
}