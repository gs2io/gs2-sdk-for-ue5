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

#include "Ranking/Request/GetRankingRequest.h"

namespace Gs2::Ranking::Request
{
    FGetRankingRequest::FGetRankingRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        AccessTokenValue(TOptional<FString>()),
        ScorerUserIdValue(TOptional<FString>()),
        UniqueIdValue(TOptional<FString>()),
        AdditionalScopeNameValue(TOptional<FString>())
    {
    }

    FGetRankingRequest::FGetRankingRequest(
        const FGetRankingRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue),
        AccessTokenValue(From.AccessTokenValue),
        ScorerUserIdValue(From.ScorerUserIdValue),
        UniqueIdValue(From.UniqueIdValue),
        AdditionalScopeNameValue(From.AdditionalScopeNameValue)
    {
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::WithAccessToken(
        const TOptional<FString> AccessToken
    )
    {
        this->AccessTokenValue = AccessToken;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::WithScorerUserId(
        const TOptional<FString> ScorerUserId
    )
    {
        this->ScorerUserIdValue = ScorerUserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::WithUniqueId(
        const TOptional<FString> UniqueId
    )
    {
        this->UniqueIdValue = UniqueId;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::WithAdditionalScopeName(
        const TOptional<FString> AdditionalScopeName
    )
    {
        this->AdditionalScopeNameValue = AdditionalScopeName;
        return SharedThis(this);
    }

    TOptional<FString> FGetRankingRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetRankingRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetRankingRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<FString> FGetRankingRequest::GetAccessToken() const
    {
        return AccessTokenValue;
    }

    TOptional<FString> FGetRankingRequest::GetScorerUserId() const
    {
        return ScorerUserIdValue;
    }

    TOptional<FString> FGetRankingRequest::GetUniqueId() const
    {
        return UniqueIdValue;
    }

    TOptional<FString> FGetRankingRequest::GetAdditionalScopeName() const
    {
        return AdditionalScopeNameValue;
    }

    TSharedPtr<FGetRankingRequest> FGetRankingRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetRankingRequest>()
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
            ->WithCategoryName(Data->HasField("categoryName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("categoryName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAccessToken(Data->HasField("xGs2AccessToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("xGs2AccessToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithScorerUserId(Data->HasField("scorerUserId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("scorerUserId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithUniqueId(Data->HasField("uniqueId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("uniqueId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAdditionalScopeName(Data->HasField("additionalScopeName") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("additionalScopeName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetRankingRequest::ToJson() const
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
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
        }
        if (AccessTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("xGs2AccessToken", AccessTokenValue.GetValue());
        }
        if (ScorerUserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("scorerUserId", ScorerUserIdValue.GetValue());
        }
        if (UniqueIdValue.IsSet())
        {
            JsonRootObject->SetStringField("uniqueId", UniqueIdValue.GetValue());
        }
        if (AdditionalScopeNameValue.IsSet())
        {
            JsonRootObject->SetStringField("additionalScopeName", AdditionalScopeNameValue.GetValue());
        }
        return JsonRootObject;
    }
}