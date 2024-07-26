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

#include "Friend/Model/CancelRequestNotification.h"

namespace Gs2::Friend::Model
{

    TSharedPtr<FCancelRequestNotification> FCancelRequestNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FCancelRequestNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FCancelRequestNotification> FCancelRequestNotification::WithUserId(
        const TOptional<FString> UserId
    ) {
        UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<FString> FCancelRequestNotification::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<FCancelRequestNotification> FCancelRequestNotification::WithFromUserId(
        const TOptional<FString> FromUserId
    ) {
        FromUserIdValue = FromUserId;
        return SharedThis(this);
    }
    TOptional<FString> FCancelRequestNotification::GetFromUserId() const
    {
        return FromUserIdValue;
    }

    TSharedPtr<FCancelRequestNotification> FCancelRequestNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCancelRequestNotification>()
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
