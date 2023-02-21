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

#include "Mission/Request/DeleteCompleteByUserIdRequest.h"

namespace Gs2::Mission::Request
{
    FDeleteCompleteByUserIdRequest::FDeleteCompleteByUserIdRequest():
        NamespaceNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        MissionGroupNameValue(TOptional<FString>())
    {
    }

    FDeleteCompleteByUserIdRequest::FDeleteCompleteByUserIdRequest(
        const FDeleteCompleteByUserIdRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        UserIdValue(From.UserIdValue),
        MissionGroupNameValue(From.MissionGroupNameValue)
    {
    }

    TSharedPtr<FDeleteCompleteByUserIdRequest> FDeleteCompleteByUserIdRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteCompleteByUserIdRequest> FDeleteCompleteByUserIdRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteCompleteByUserIdRequest> FDeleteCompleteByUserIdRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteCompleteByUserIdRequest> FDeleteCompleteByUserIdRequest::WithMissionGroupName(
        const TOptional<FString> MissionGroupName
    )
    {
        this->MissionGroupNameValue = MissionGroupName;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteCompleteByUserIdRequest> FDeleteCompleteByUserIdRequest::WithDuplicationAvoider(
        const TOptional<FString> DuplicationAvoider
    )
    {
        this->DuplicationAvoiderValue = DuplicationAvoider;
        return SharedThis(this);
    }

    TOptional<FString> FDeleteCompleteByUserIdRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDeleteCompleteByUserIdRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDeleteCompleteByUserIdRequest::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<FString> FDeleteCompleteByUserIdRequest::GetMissionGroupName() const
    {
        return MissionGroupNameValue;
    }

    TOptional<FString> FDeleteCompleteByUserIdRequest::GetDuplicationAvoider() const
    {
        return DuplicationAvoiderValue;
    }

    TSharedPtr<FDeleteCompleteByUserIdRequest> FDeleteCompleteByUserIdRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteCompleteByUserIdRequest>()
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
            ->WithMissionGroupName(Data->HasField("missionGroupName") ? [Data]() -> TOptional<FString>
              {
                  FString v;
                    if (Data->TryGetStringField("missionGroupName", v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
          ->WithDuplicationAvoider(Data->HasField("duplicationAvoider") ? TOptional<FString>(Data->GetStringField("duplicationAvoider")) : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FDeleteCompleteByUserIdRequest::ToJson() const
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
        if (MissionGroupNameValue.IsSet())
        {
            JsonRootObject->SetStringField("missionGroupName", MissionGroupNameValue.GetValue());
        }
        if (DuplicationAvoiderValue.IsSet())
        {
            JsonRootObject->SetStringField("duplicationAvoider", DuplicationAvoiderValue.GetValue());
        }
        return JsonRootObject;
    }
}