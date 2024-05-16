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

#include "SeasonRating/Request/UpdateSeasonModelMasterRequest.h"

namespace Gs2::SeasonRating::Request
{
    FUpdateSeasonModelMasterRequest::FUpdateSeasonModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        SeasonNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        TiersValue(nullptr),
        ExperienceModelIdValue(TOptional<FString>()),
        ChallengePeriodEventIdValue(TOptional<FString>())
    {
    }

    FUpdateSeasonModelMasterRequest::FUpdateSeasonModelMasterRequest(
        const FUpdateSeasonModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        SeasonNameValue(From.SeasonNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        TiersValue(From.TiersValue),
        ExperienceModelIdValue(From.ExperienceModelIdValue),
        ChallengePeriodEventIdValue(From.ChallengePeriodEventIdValue)
    {
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithSeasonName(
        const TOptional<FString> SeasonName
    )
    {
        this->SeasonNameValue = SeasonName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithTiers(
        const TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> Tiers
    )
    {
        this->TiersValue = Tiers;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithExperienceModelId(
        const TOptional<FString> ExperienceModelId
    )
    {
        this->ExperienceModelIdValue = ExperienceModelId;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateSeasonModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateSeasonModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateSeasonModelMasterRequest::GetSeasonName() const
    {
        return SeasonNameValue;
    }

    TOptional<FString> FUpdateSeasonModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateSeasonModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<TArray<TSharedPtr<Model::FTierModel>>> FUpdateSeasonModelMasterRequest::GetTiers() const
    {
        if (!TiersValue.IsValid())
        {
            return nullptr;
        }
        return TiersValue;
    }

    TOptional<FString> FUpdateSeasonModelMasterRequest::GetExperienceModelId() const
    {
        return ExperienceModelIdValue;
    }

    TOptional<FString> FUpdateSeasonModelMasterRequest::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    TSharedPtr<FUpdateSeasonModelMasterRequest> FUpdateSeasonModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateSeasonModelMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithSeasonName(Data->HasField(ANSI_TO_TCHAR("seasonName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("seasonName"), v))
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
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithTiers(Data->HasField(ANSI_TO_TCHAR("tiers")) ? [Data]() -> TSharedPtr<TArray<Model::FTierModelPtr>>
              {
                  auto v = MakeShared<TArray<Model::FTierModelPtr>>();
                  if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("tiers")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("tiers")))
                  {
                      for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("tiers")))
                      {
                          v->Add(Model::FTierModel::FromJson(JsonObjectValue->AsObject()));
                      }
                  }
                  return v;
              }() : MakeShared<TArray<Model::FTierModelPtr>>())
            ->WithExperienceModelId(Data->HasField(ANSI_TO_TCHAR("experienceModelId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("experienceModelId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithChallengePeriodEventId(Data->HasField(ANSI_TO_TCHAR("challengePeriodEventId")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("challengePeriodEventId"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateSeasonModelMasterRequest::ToJson() const
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
        if (SeasonNameValue.IsSet())
        {
            JsonRootObject->SetStringField("seasonName", SeasonNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (TiersValue != nullptr && TiersValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *TiersValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("tiers", v);
        }
        if (ExperienceModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceModelId", ExperienceModelIdValue.GetValue());
        }
        if (ChallengePeriodEventIdValue.IsSet())
        {
            JsonRootObject->SetStringField("challengePeriodEventId", ChallengePeriodEventIdValue.GetValue());
        }
        return JsonRootObject;
    }
}