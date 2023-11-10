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

#include "Experience/Request/CreateExperienceModelMasterRequest.h"

namespace Gs2::Experience::Request
{
    FCreateExperienceModelMasterRequest::FCreateExperienceModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultExperienceValue(TOptional<int64>()),
        DefaultRankCapValue(TOptional<int64>()),
        MaxRankCapValue(TOptional<int64>()),
        RankThresholdNameValue(TOptional<FString>()),
        AcquireActionRatesValue(nullptr)
    {
    }

    FCreateExperienceModelMasterRequest::FCreateExperienceModelMasterRequest(
        const FCreateExperienceModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        DefaultExperienceValue(From.DefaultExperienceValue),
        DefaultRankCapValue(From.DefaultRankCapValue),
        MaxRankCapValue(From.MaxRankCapValue),
        RankThresholdNameValue(From.RankThresholdNameValue),
        AcquireActionRatesValue(From.AcquireActionRatesValue)
    {
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithDefaultExperience(
        const TOptional<int64> DefaultExperience
    )
    {
        this->DefaultExperienceValue = DefaultExperience;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithDefaultRankCap(
        const TOptional<int64> DefaultRankCap
    )
    {
        this->DefaultRankCapValue = DefaultRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithMaxRankCap(
        const TOptional<int64> MaxRankCap
    )
    {
        this->MaxRankCapValue = MaxRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithRankThresholdName(
        const TOptional<FString> RankThresholdName
    )
    {
        this->RankThresholdNameValue = RankThresholdName;
        return SharedThis(this);
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::WithAcquireActionRates(
        const TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> AcquireActionRates
    )
    {
        this->AcquireActionRatesValue = AcquireActionRates;
        return SharedThis(this);
    }

    TOptional<FString> FCreateExperienceModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FCreateExperienceModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FCreateExperienceModelMasterRequest::GetName() const
    {
        return NameValue;
    }

    TOptional<FString> FCreateExperienceModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FCreateExperienceModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int64> FCreateExperienceModelMasterRequest::GetDefaultExperience() const
    {
        return DefaultExperienceValue;
    }

    FString FCreateExperienceModelMasterRequest::GetDefaultExperienceString() const
    {
        if (!DefaultExperienceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue());
    }

    TOptional<int64> FCreateExperienceModelMasterRequest::GetDefaultRankCap() const
    {
        return DefaultRankCapValue;
    }

    FString FCreateExperienceModelMasterRequest::GetDefaultRankCapString() const
    {
        if (!DefaultRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue());
    }

    TOptional<int64> FCreateExperienceModelMasterRequest::GetMaxRankCap() const
    {
        return MaxRankCapValue;
    }

    FString FCreateExperienceModelMasterRequest::GetMaxRankCapString() const
    {
        if (!MaxRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue());
    }

    TOptional<FString> FCreateExperienceModelMasterRequest::GetRankThresholdName() const
    {
        return RankThresholdNameValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FAcquireActionRate>>> FCreateExperienceModelMasterRequest::GetAcquireActionRates() const
    {
        if (!AcquireActionRatesValue.IsValid())
        {
            return nullptr;
        }
        return AcquireActionRatesValue;
    }

    TSharedPtr<FCreateExperienceModelMasterRequest> FCreateExperienceModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCreateExperienceModelMasterRequest>()
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("metadata", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithDefaultExperience(Data->HasField("defaultExperience") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("defaultExperience", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithDefaultRankCap(Data->HasField("defaultRankCap") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("defaultRankCap", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithMaxRankCap(Data->HasField("maxRankCap") ? [Data]() -> TOptional<int64>
              {
                  int64 v;
                    if (Data->TryGetNumberField("maxRankCap", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int64>();
              }() : TOptional<int64>())
            ->WithRankThresholdName(Data->HasField("rankThresholdName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("rankThresholdName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithAcquireActionRates(Data->HasField("acquireActionRates") ? [Data]() -> TSharedPtr<TArray<Model::FAcquireActionRatePtr>>
              {
                  auto v = MakeShared<TArray<Model::FAcquireActionRatePtr>>();
                  if (!Data->HasTypedField<EJson::Null>("acquireActionRates") && Data->HasTypedField<EJson::Array>("acquireActionRates"))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField("acquireActionRates"))
                      {
                          v->Add(Model::FAcquireActionRate::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
             }() : nullptr);
    }

    TSharedPtr<FJsonObject> FCreateExperienceModelMasterRequest::ToJson() const
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
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DefaultExperienceValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultExperience", FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue()));
        }
        if (DefaultRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultRankCap", FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue()));
        }
        if (MaxRankCapValue.IsSet())
        {
            JsonRootObject->SetStringField("maxRankCap", FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue()));
        }
        if (RankThresholdNameValue.IsSet())
        {
            JsonRootObject->SetStringField("rankThresholdName", RankThresholdNameValue.GetValue());
        }
        if (AcquireActionRatesValue != nullptr && AcquireActionRatesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *AcquireActionRatesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("acquireActionRates", v);
        }
        return JsonRootObject;
    }
}