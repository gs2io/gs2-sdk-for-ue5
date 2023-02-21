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

#include "Gateway/Request/SetUserIdByUserIdRequest.h"

namespace Gs2::Gateway::Request
{
    FSetUserIdByUserIdRequest::FSetUserIdByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        AllowConcurrentAccessValue(TOptional<bool>())
    {
    }

    FSetUserIdByUserIdRequest::FSetUserIdByUserIdRequest(
        const FSetUserIdByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        AllowConcurrentAccessValue(From.AllowConcurrentAccessValue)
    {
    }

    TSharedPtr<FSetUserIdByUserIdRequest> FSetUserIdByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FSetUserIdByUserIdRequest> FSetUserIdByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FSetUserIdByUserIdRequest> FSetUserIdByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FSetUserIdByUserIdRequest> FSetUserIdByUserIdRequest::WithAllowConcurrentAccess(
        const TOptional<bool> AllowConcurrentAccess
    )
    {
        this->AllowConcurrentAccessValue = AllowConcurrentAccess;
        return SharedThis(this);
    }

    TSharedPtr<FSetUserIdByUserIdRequest> FSetUserIdByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FSetUserIdByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FSetUserIdByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FSetUserIdByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<bool> FSetUserIdByUserIdRequest::GetAllowConcurrentAccess() const
    {
        return AllowConcurrentAccessValue;
    }

    FString FSetUserIdByUserIdRequest::GetAllowConcurrentAccessString() const
    {
        if (!AllowConcurrentAccessValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowConcurrentAccessValue.GetValue() ? "true" : "false");
    }

    TOptional<FString> FSetUserIdByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FSetUserIdByUserIdRequest> FSetUserIdByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetUserIdByUserIdRequest>()
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
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("userId", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithAllowConcurrentAccess(Data->HasField("allowConcurrentAccess") ? [Data]() -> TOptional<bool>
              {
                  bool v;
                    if (Data->TryGetBoolField("allowConcurrentAccess", v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<bool>();
              }() : TOptional<bool>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSetUserIdByUserIdRequest::ToJson() const
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
        if (AllowConcurrentAccessValue.IsSet())
        {
            JsonRootObject->SetBoolField("allowConcurrentAccess", AllowConcurrentAccessValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}