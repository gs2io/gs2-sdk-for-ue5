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

#include "Experience/Request/UpdateExperienceModelMasterRequest.h"

namespace Gs2::Experience::Request
{
    FUpdateExperienceModelMasterRequest::FUpdateExperienceModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        ExperienceNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultExperienceValue(TOptional<int64>()),
        DefaultRankCapValue(TOptional<int64>()),
        MaxRankCapValue(TOptional<int64>()),
        RankThresholdNameValue(TOptional<FString>())
    {
    }

    FUpdateExperienceModelMasterRequest::FUpdateExperienceModelMasterRequest(
        const FUpdateExperienceModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        ExperienceNameValue(From.ExperienceNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        DefaultExperienceValue(From.DefaultExperienceValue),
        DefaultRankCapValue(From.DefaultRankCapValue),
        MaxRankCapValue(From.MaxRankCapValue),
        RankThresholdNameValue(From.RankThresholdNameValue)
    {
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithExperienceName(
        const TOptional<FString> ExperienceName
    )
    {
        this->ExperienceNameValue = ExperienceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithDefaultExperience(
        const TOptional<int64> DefaultExperience
    )
    {
        this->DefaultExperienceValue = DefaultExperience;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithDefaultRankCap(
        const TOptional<int64> DefaultRankCap
    )
    {
        this->DefaultRankCapValue = DefaultRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithMaxRankCap(
        const TOptional<int64> MaxRankCap
    )
    {
        this->MaxRankCapValue = MaxRankCap;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::WithRankThresholdName(
        const TOptional<FString> RankThresholdName
    )
    {
        this->RankThresholdNameValue = RankThresholdName;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateExperienceModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateExperienceModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateExperienceModelMasterRequest::GetExperienceName() const
    {
        return ExperienceNameValue;
    }

    TOptional<FString> FUpdateExperienceModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateExperienceModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int64> FUpdateExperienceModelMasterRequest::GetDefaultExperience() const
    {
        return DefaultExperienceValue;
    }

    FString FUpdateExperienceModelMasterRequest::GetDefaultExperienceString() const
    {
        if (!DefaultExperienceValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultExperienceValue.GetValue());
    }

    TOptional<int64> FUpdateExperienceModelMasterRequest::GetDefaultRankCap() const
    {
        return DefaultRankCapValue;
    }

    FString FUpdateExperienceModelMasterRequest::GetDefaultRankCapString() const
    {
        if (!DefaultRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultRankCapValue.GetValue());
    }

    TOptional<int64> FUpdateExperienceModelMasterRequest::GetMaxRankCap() const
    {
        return MaxRankCapValue;
    }

    FString FUpdateExperienceModelMasterRequest::GetMaxRankCapString() const
    {
        if (!MaxRankCapValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), MaxRankCapValue.GetValue());
    }

    TOptional<FString> FUpdateExperienceModelMasterRequest::GetRankThresholdName() const
    {
        return RankThresholdNameValue;
    }

    TSharedPtr<FUpdateExperienceModelMasterRequest> FUpdateExperienceModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateExperienceModelMasterRequest>()
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
            ->WithExperienceName(Data->HasField("experienceName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("experienceName", v))
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
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
              {
                  FString v;
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
                  FString v;
                    if (Data->TryGetStringField("rankThresholdName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FUpdateExperienceModelMasterRequest::ToJson() const
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
        if (ExperienceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("experienceName", ExperienceNameValue.GetValue());
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
        return JsonRootObject;
    }
}