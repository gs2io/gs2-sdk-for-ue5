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

#include "Matchmaking/Request/GetRatingModelMasterRequest.h"

namespace Gs2::Matchmaking::Request
{
    FGetRatingModelMasterRequest::FGetRatingModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        RatingNameValue(TOptional<FString>())
    {
    }

    FGetRatingModelMasterRequest::FGetRatingModelMasterRequest(
        const FGetRatingModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        RatingNameValue(From.RatingNameValue)
    {
    }

    TSharedPtr<FGetRatingModelMasterRequest> FGetRatingModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetRatingModelMasterRequest> FGetRatingModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetRatingModelMasterRequest> FGetRatingModelMasterRequest::WithRatingName(
        const TOptional<FString> RatingName
    )
    {
        this->RatingNameValue = RatingName;
        return SharedThis(this);
    }

    TOptional<FString> FGetRatingModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetRatingModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetRatingModelMasterRequest::GetRatingName() const
    {
        return RatingNameValue;
    }

    TSharedPtr<FGetRatingModelMasterRequest> FGetRatingModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetRatingModelMasterRequest>()
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
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetRatingModelMasterRequest::ToJson() const
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
        return JsonRootObject;
    }
}