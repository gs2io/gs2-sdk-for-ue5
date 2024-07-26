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

#include "Friend/Model/ReceiveRequestNotification.h"

namespace Gs2::Friend::Model
{

    TSharedPtr<FReceiveRequestNotification> FReceiveRequestNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FReceiveRequestNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FReceiveRequestNotification> FReceiveRequestNotification::WithUserId(
        const TOptional<FString> UserId
    ) {
        UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<FString> FReceiveRequestNotification::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<FReceiveRequestNotification> FReceiveRequestNotification::WithFromUserId(
        const TOptional<FString> FromUserId
    ) {
        FromUserIdValue = FromUserId;
        return SharedThis(this);
    }
    TOptional<FString> FReceiveRequestNotification::GetFromUserId() const
    {
        return FromUserIdValue;
    }

    TSharedPtr<FReceiveRequestNotification> FReceiveRequestNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FReceiveRequestNotification>()
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithFromUserId(Data->HasField(ANSI_TO_TCHAR("fromUserId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("fromUserId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
