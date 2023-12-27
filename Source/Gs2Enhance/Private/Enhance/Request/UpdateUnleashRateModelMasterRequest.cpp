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

#include "Enhance/Request/UpdateUnleashRateModelMasterRequest.h"

namespace Gs2::Enhance::Request
{
    FUpdateUnleashRateModelMasterRequest::FUpdateUnleashRateModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TargetInventoryModelIdValue(TOptional<FString>()),
        GradeModelIdValue(TOptional<FString>()),
        GradeEntriesValue(nullptr)
    {
    }

    FUpdateUnleashRateModelMasterRequest::FUpdateUnleashRateModelMasterRequest(
        const FUpdateUnleashRateModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RateNameValue(From.RateNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        TargetInventoryModelIdValue(From.TargetInventoryModelIdValue),
        GradeModelIdValue(From.GradeModelIdValue),
        GradeEntriesValue(From.GradeEntriesValue)
    {
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithTargetInventoryModelId(
        const TOptional<FString> TargetInventoryModelId
    )
    {
        this->TargetInventoryModelIdValue = TargetInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithGradeModelId(
        const TOptional<FString> GradeModelId
    )
    {
        this->GradeModelIdValue = GradeModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::WithGradeEntries(
        const TSharedPtr<TArray<TSharedPtr<Model::FUnleashRateEntryModel>>> GradeEntries
    )
    {
        this->GradeEntriesValue = GradeEntries;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateUnleashRateModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateUnleashRateModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateUnleashRateModelMasterRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TOptional<FString> FUpdateUnleashRateModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateUnleashRateModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateUnleashRateModelMasterRequest::GetTargetInventoryModelId() const
    {
        return TargetInventoryModelIdValue;
    }

    TOptional<FString> FUpdateUnleashRateModelMasterRequest::GetGradeModelId() const
    {
        return GradeModelIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FUnleashRateEntryModel>>> FUpdateUnleashRateModelMasterRequest::GetGradeEntries() const
    {
        if (!GradeEntriesValue.IsValid())
        {
            return nullptr;
        }
        return GradeEntriesValue;
    }

    TSharedPtr<FUpdateUnleashRateModelMasterRequest> FUpdateUnleashRateModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateUnleashRateModelMasterRequest>()
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
            ->WithRateName(Data->HasField("rateName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("rateName", v))
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
            ->WithTargetInventoryModelId(Data->HasField("targetInventoryModelId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("targetInventoryModelId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithGradeModelId(Data->HasField("gradeModelId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("gradeModelId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithGradeEntries(Data->HasField("gradeEntries") ? [Data]() -> TSharedPtr<TArray<Model::FUnleashRateEntryModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FUnleashRateEntryModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>("gradeEntries") && Data->HasTypedField<EJson::Array>("gradeEntries"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("gradeEntries"))
                      {
                          v->Add(Model::FUnleashRateEntryModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUpdateUnleashRateModelMasterRequest::ToJson() const
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
        if (RateNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rateName", RateNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (TargetInventoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("targetInventoryModelId", TargetInventoryModelIdValue.GetValue());
        }
        if (GradeModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeModelId", GradeModelIdValue.GetValue());
        }
        if (GradeEntriesValue != nullptr && GradeEntriesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *GradeEntriesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("gradeEntries", v);
        }
        return JsonRootObject;
    }
}