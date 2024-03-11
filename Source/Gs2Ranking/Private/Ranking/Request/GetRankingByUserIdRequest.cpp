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

#include "Ranking/Request/GetRankingByUserIdRequest.h"

namespace Gs2::Ranking::Request
{
    FGetRankingByUserIdRequest::FGetRankingByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ScorerUserIdValue(TOptional<FString>()),
        UniqueIdValue(TOptional<FString>()),
        AdditionalScopeNameValue(TOptional<FString>()),
        TimeOffsetTokenValue(TOptional<FString>())
    {
    }

    FGetRankingByUserIdRequest::FGetRankingByUserIdRequest(
        const FGetRankingByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CategoryNameValue(From.CategoryNameValue),
        UserIdValue(From.UserIdValue),
        ScorerUserIdValue(From.ScorerUserIdValue),
        UniqueIdValue(From.UniqueIdValue),
        AdditionalScopeNameValue(From.AdditionalScopeNameValue),
        TimeOffsetTokenValue(From.TimeOffsetTokenValue)
    {
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithScorerUserId(
        const TOptional<FString> ScorerUserId
    )
    {
        this->ScorerUserIdValue = ScorerUserId;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithUniqueId(
        const TOptional<FString> UniqueId
    )
    {
        this->UniqueIdValue = UniqueId;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithAdditionalScopeName(
        const TOptional<FString> AdditionalScopeName
    )
    {
        this->AdditionalScopeNameValue = AdditionalScopeName;
        return SharedThis(this);
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::WithTimeOffsetToken(
        const TOptional<FString> TimeOffsetToken
    )
    {
        this->TimeOffsetTokenValue = TimeOffsetToken;
        return SharedThis(this);
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetScorerUserId() const
    {
        return ScorerUserIdValue;
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetUniqueId() const
    {
        return UniqueIdValue;
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetAdditionalScopeName() const
    {
        return AdditionalScopeNameValue;
    }

    TOptional<FString> FGetRankingByUserIdRequest::GetTimeOffsetToken() const
    {
        return TimeOffsetTokenValue;
    }

    TSharedPtr<FGetRankingByUserIdRequest> FGetRankingByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetRankingByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
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
              }() : TOptional<FString>())
            ->WithTimeOffsetToken(Data->HasField("timeOffsetToken") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("timeOffsetToken", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGetRankingByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
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
        if (TimeOffsetTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("timeOffsetToken", TimeOffsetTokenValue.GetValue());
        }
        return JsonRootObject;
    }
}