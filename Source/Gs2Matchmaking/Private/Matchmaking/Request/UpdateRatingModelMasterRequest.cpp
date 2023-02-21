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

#include "Matchmaking/Request/UpdateRatingModelMasterRequest.h"

namespace Gs2::Matchmaking::Request
{
    FUpdateRatingModelMasterRequest::FUpdateRatingModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RatingNameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        VolatilityValue(TOptional<int32>())
    {
    }

    FUpdateRatingModelMasterRequest::FUpdateRatingModelMasterRequest(
        const FUpdateRatingModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RatingNameValue(From.RatingNameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        VolatilityValue(From.VolatilityValue)
    {
    }

    TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequest::WithRatingName(
        const TOptional<FString> RatingName
    )
    {
        this->RatingNameValue = RatingName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequest::WithVolatility(
        const TOptional<int32> Volatility
    )
    {
        this->VolatilityValue = Volatility;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateRatingModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateRatingModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateRatingModelMasterRequest::GetRatingName() const
    {
        return RatingNameValue;
    }

    TOptional<FString> FUpdateRatingModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateRatingModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FUpdateRatingModelMasterRequest::GetVolatility() const
    {
        return VolatilityValue;
    }

    FString FUpdateRatingModelMasterRequest::GetVolatilityString() const
    {
        if (!VolatilityValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), VolatilityValue.GetValue());
    }

    TSharedPtr<FUpdateRatingModelMasterRequest> FUpdateRatingModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateRatingModelMasterRequest>()
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
            ->WithRatingName(Data->HasField("ratingName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("ratingName", v))
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
            ->WithVolatility(Data->HasField("volatility") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("volatility", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUpdateRatingModelMasterRequest::ToJson() const
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
        if (RatingNameValue.IsSet())
        {
            JsonRootObject->SetStringField("ratingName", RatingNameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (VolatilityValue.IsSet())
        {
            JsonRootObject->SetNumberField("volatility", VolatilityValue.GetValue());
        }
        return JsonRootObject;
    }
}