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

#include "Money2/Model/ChangeSubscriptionStatusNotification.h"

namespace Gs2::Money2::Model
{

    TSharedPtr<FChangeSubscriptionStatusNotification> FChangeSubscriptionStatusNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FChangeSubscriptionStatusNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FChangeSubscriptionStatusNotification> FChangeSubscriptionStatusNotification::WithUserId(
        const TOptional<FString> UserId
    ) {
        UserIdValue = UserId;
        return SharedThis(this);
    }
    TOptional<FString> FChangeSubscriptionStatusNotification::GetUserId() const
    {
        return UserIdValue;
    }

    TSharedPtr<FChangeSubscriptionStatusNotification> FChangeSubscriptionStatusNotification::WithContentName(
        const TOptional<FString> ContentName
    ) {
        ContentNameValue = ContentName;
        return SharedThis(this);
    }
    TOptional<FString> FChangeSubscriptionStatusNotification::GetContentName() const
    {
        return ContentNameValue;
    }

    TSharedPtr<FChangeSubscriptionStatusNotification> FChangeSubscriptionStatusNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FChangeSubscriptionStatusNotification>()
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
            ->WithContentName(Data->HasField(ANSI_TO_TCHAR("contentName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("contentName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
