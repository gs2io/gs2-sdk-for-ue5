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

#include "Idle/Request/DecreaseMaximumIdleMinutesByUserIdRequest.h"

namespace Gs2::Idle::Request
{
    FDecreaseMaximumIdleMinutesByUserIdRequest::FDecreaseMaximumIdleMinutesByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        CategoryNameValue(TOptional<FString>()),
        DecreaseMinutesValue(TOptional<int32>())
    {
    }

    FDecreaseMaximumIdleMinutesByUserIdRequest::FDecreaseMaximumIdleMinutesByUserIdRequest(
        const FDecreaseMaximumIdleMinutesByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        CategoryNameValue(From.CategoryNameValue),
        DecreaseMinutesValue(From.DecreaseMinutesValue)
    {
    }

    TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequest::WithCategoryName(
        const TOptional<FString> CategoryName
    )
    {
        this->CategoryNameValue = CategoryName;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequest::WithDecreaseMinutes(
        const TOptional<int32> DecreaseMinutes
    )
    {
        this->DecreaseMinutesValue = DecreaseMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDecreaseMaximumIdleMinutesByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDecreaseMaximumIdleMinutesByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDecreaseMaximumIdleMinutesByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FDecreaseMaximumIdleMinutesByUserIdRequest::GetCategoryName() const
    {
        return CategoryNameValue;
    }

    TOptional<int32> FDecreaseMaximumIdleMinutesByUserIdRequest::GetDecreaseMinutes() const
    {
        return DecreaseMinutesValue;
    }

    FString FDecreaseMaximumIdleMinutesByUserIdRequest::GetDecreaseMinutesString() const
    {
        if (!DecreaseMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DecreaseMinutesValue.GetValue());
    }

    TOptional<FString> FDecreaseMaximumIdleMinutesByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDecreaseMaximumIdleMinutesByUserIdRequest> FDecreaseMaximumIdleMinutesByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDecreaseMaximumIdleMinutesByUserIdRequest>()
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
            ->WithDecreaseMinutes(Data->HasField("decreaseMinutes") ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField("decreaseMinutes", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDecreaseMaximumIdleMinutesByUserIdRequest::ToJson() const
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
        if (DecreaseMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("decreaseMinutes", DecreaseMinutesValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}