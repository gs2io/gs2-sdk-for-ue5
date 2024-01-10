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

#include "Enhance/Request/UpdateRateModelMasterRequest.h"

namespace Gs2::Enhance::Request
{
    FUpdateRateModelMasterRequest::FUpdateRateModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RateNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TargetInventoryModelIdValue(TOptional<FString>()),
        AcquireExperienceSuffixValue(TOptional<FString>()),
        MaterialInventoryModelIdValue(TOptional<FString>()),
        AcquireExperienceHierarchyValue(nullptr),
        ExperienceModelIdValue(TOptional<FString>()),
        BonusRatesValue(nullptr)
    {
    }

    FUpdateRateModelMasterRequest::FUpdateRateModelMasterRequest(
        const FUpdateRateModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RateNameValue(From.RateNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        TargetInventoryModelIdValue(From.TargetInventoryModelIdValue),
        AcquireExperienceSuffixValue(From.AcquireExperienceSuffixValue),
        MaterialInventoryModelIdValue(From.MaterialInventoryModelIdValue),
        AcquireExperienceHierarchyValue(From.AcquireExperienceHierarchyValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        BonusRatesValue(From.BonusRatesValue)
    {
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithRateName(
        const TOptional<FString> RateName
    )
    {
        this->RateNameValue = RateName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithTargetInventoryModelId(
        const TOptional<FString> TargetInventoryModelId
    )
    {
        this->TargetInventoryModelIdValue = TargetInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithAcquireExperienceSuffix(
        const TOptional<FString> AcquireExperienceSuffix
    )
    {
        this->AcquireExperienceSuffixValue = AcquireExperienceSuffix;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithMaterialInventoryModelId(
        const TOptional<FString> MaterialInventoryModelId
    )
    {
        this->MaterialInventoryModelIdValue = MaterialInventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithAcquireExperienceHierarchy(
        const TSharedPtr<TArray<FString>> AcquireExperienceHierarchy
    )
    {
        this->AcquireExperienceHierarchyValue = AcquireExperienceHierarchy;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::WithBonusRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> BonusRates
    )
    {
        this->BonusRatesValue = BonusRates;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetRateName() const
    {
        return RateNameValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetTargetInventoryModelId() const
    {
        return TargetInventoryModelIdValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetAcquireExperienceSuffix() const
    {
        return AcquireExperienceSuffixValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetMaterialInventoryModelId() const
    {
        return MaterialInventoryModelIdValue;
    }

    TSharedPtr<TArray<FString>> FUpdateRateModelMasterRequest::GetAcquireExperienceHierarchy() const
    {
        if (!AcquireExperienceHierarchyValue.IsValid())
        {
            return nullptr;
        }
        return AcquireExperienceHierarchyValue;
    }

    TOptional<FString> FUpdateRateModelMasterRequest::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FBonusRate>>> FUpdateRateModelMasterRequest::GetBonusRates() const
    {
        if (!BonusRatesValue.IsValid())
        {
            return nullptr;
        }
        return BonusRatesValue;
    }

    TSharedPtr<FUpdateRateModelMasterRequest> FUpdateRateModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateRateModelMasterRequest>()
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
            ->WithAcquireExperienceSuffix(Data->HasField("acquireExperienceSuffix") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("acquireExperienceSuffix", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithMaterialInventoryModelId(Data->HasField("materialInventoryModelId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("materialInventoryModelId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAcquireExperienceHierarchy(Data->HasField("acquireExperienceHierarchy") ? [Data]() -> TSharedPtr<TArray<FString>>
              {
                  auto v = MakeShared<TArray<FString>>();
                  if (!Data->HasTypedField<EJson::Null>("acquireExperienceHierarchy") && Data->HasTypedField<EJson::Array>("acquireExperienceHierarchy"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("acquireExperienceHierarchy"))
                      {
                          v->Add(JsonObjectValue->AsString());
                      }
                  }
                  return v;
              }() : MakeShared<TArray<FString>>())
            ->WithExperienceModelId(Data->HasField("experienceModelId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("experienceModelId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithBonusRates(Data->HasField("bonusRates") ? [Data]() -> TSharedPtr<TArray<Model::FBonusRatePtr>>
              {
                  auto v = MakeShared<TArray<Model::FBonusRatePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("bonusRates") && Data->HasTypedField<EJson::Array>("bonusRates"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("bonusRates"))
                      {
                          v->Add(Model::FBonusRate::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FBonusRatePtr>>());
    }

    TSharedPtr<FJsonObject> FUpdateRateModelMasterRequest::ToJson() const
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
        if (AcquireExperienceSuffixValue.IsSet())
        {
            JsonRootObject->SetStringField("acquireExperienceSuffix", AcquireExperienceSuffixValue.GetValue());
        }
        if (MaterialInventoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("materialInventoryModelId", MaterialInventoryModelIdValue.GetValue());
        }
        if (AcquireExperienceHierarchyValue != nullptr && AcquireExperienceHierarchyValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireExperienceHierarchyValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField("acquireExperienceHierarchy", v);
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (BonusRatesValue != nullptr && BonusRatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *BonusRatesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("bonusRates", v);
        }
        return JsonRootObject;
    }
}