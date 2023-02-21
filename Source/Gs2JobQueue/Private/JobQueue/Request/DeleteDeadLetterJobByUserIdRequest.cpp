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

#include "JobQueue/Request/DeleteDeadLetterJobByUserIdRequest.h"

namespace Gs2::JobQueue::Request
{
    FDeleteDeadLetterJobByUserIdRequest::FDeleteDeadLetterJobByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        DeadLetterJobNameValue(TOptional<FString>())
    {
    }

    FDeleteDeadLetterJobByUserIdRequest::FDeleteDeadLetterJobByUserIdRequest(
        const FDeleteDeadLetterJobByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        DeadLetterJobNameValue(From.DeadLetterJobNameValue)
    {
    }

    TSharedPtr<FDeleteDeadLetterJobByUserIdRequest> FDeleteDeadLetterJobByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDeadLetterJobByUserIdRequest> FDeleteDeadLetterJobByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDeadLetterJobByUserIdRequest> FDeleteDeadLetterJobByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDeadLetterJobByUserIdRequest> FDeleteDeadLetterJobByUserIdRequest::WithDeadLetterJobName(
        const TOptional<FString> DeadLetterJobName
    )
    {
        this->DeadLetterJobNameValue = DeadLetterJobName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteDeadLetterJobByUserIdRequest> FDeleteDeadLetterJobByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteDeadLetterJobByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteDeadLetterJobByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteDeadLetterJobByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FDeleteDeadLetterJobByUserIdRequest::GetDeadLetterJobName() const
    {
        return DeadLetterJobNameValue;
    }

    TOptional<FString> FDeleteDeadLetterJobByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDeleteDeadLetterJobByUserIdRequest> FDeleteDeadLetterJobByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteDeadLetterJobByUserIdRequest>()
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
            ->WithDeadLetterJobName(Data->HasField("deadLetterJobName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("deadLetterJobName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteDeadLetterJobByUserIdRequest::ToJson() const
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
        if (DeadLetterJobNameValue.IsSet())
        {
            JsonRootObject->SetStringField("deadLetterJobName", DeadLetterJobNameValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}