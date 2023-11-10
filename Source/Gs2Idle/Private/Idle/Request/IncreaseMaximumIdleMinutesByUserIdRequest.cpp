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

#include "Idle/Request/IncreaseMaximumIdleMinutesByUserIdRequest.h"

namespace Gs2::Idle::Request
{
    FIncreaseMaximumIdleMinutesByUserIdRequest::FIncreaseMaximumIdleMinutesByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        IncreaseMinutesValue(TOptional<int32>())
    {
    }

    FIncreaseMaximumIdleMinutesByUserIdRequest::FIncreaseMaximumIdleMinutesByUserIdRequest(
        const FIncreaseMaximumIdleMinutesByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        CategoryNameValue(From.CategoryNameValue),
        IncreaseMinutesValue(From.IncreaseMinutesValue)
    {
    }

    TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FIncreaseMaximumIdleMinutesByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FIncreaseMaximumIdleMinutesByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FIncreaseMaximumIdleMinutesByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FIncreaseMaximumIdleMinutesByUserIdRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FIncreaseMaximumIdleMinutesByUserIdRequest::WithIncreaseMinutes(
        const TOptional<int32> IncreaseMinutes
    )
    {
        this->IncreaseMinutesValue = IncreaseMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FIncreaseMaximumIdleMinutesByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FIncreaseMaximumIdleMinutesByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FIncreaseMaximumIdleMinutesByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FIncreaseMaximumIdleMinutesByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FIncreaseMaximumIdleMinutesByUserIdRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<int32> FIncreaseMaximumIdleMinutesByUserIdRequest::GetIncreaseMinutes() const
    {
        return IncreaseMinutesValue;
    }

    FString FIncreaseMaximumIdleMinutesByUserIdRequest::GetIncreaseMinutesString() const
    {
        if (!IncreaseMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), IncreaseMinutesValue.GetValue());
    }

    TOptional<FString> FIncreaseMaximumIdleMinutesByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FIncreaseMaximumIdleMinutesByUserIdRequest> FIncreaseMaximumIdleMinutesByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FIncreaseMaximumIdleMinutesByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField("userId", v))
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
            ->WithIncreaseMinutes(Data->HasField("increaseMinutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("increaseMinutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FIncreaseMaximumIdleMinutesByUserIdRequest::ToJson() const
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
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (CategoryNameValue.IsSet())
        {
            JsonRootObject->SetStringField("categoryName", CategoryNameValue.GetValue());
        }
        if (IncreaseMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("increaseMinutes", IncreaseMinutesValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}