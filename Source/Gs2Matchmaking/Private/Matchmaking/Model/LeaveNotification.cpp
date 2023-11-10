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

#include "Matchmaking/Model/LeaveNotification.h"

namespace Gs2::Matchmaking::Model
{

    TSharedPtr<FLeaveNotification> FLeaveNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FLeaveNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FLeaveNotification> FLeaveNotification::WithGatheringName(
        const TOptional<FString> GatheringName
    ) {
        GatheringNameValue = GatheringName;
        return SharedThis(this);
    }
    TOptional<FString> FLeaveNotification::GetGatheringName() const
    {
        return GatheringNameValue;
    }

    TSharedPtr<FLeaveNotification> FLeaveNotification::WithLeaveUserId(
        const TOptional<FString> LeaveUserId
    ) {
        LeaveUserIdValue = LeaveUserId;
        return SharedThis(this);
    }
    TOptional<FString> FLeaveNotification::GetLeaveUserId() const
    {
        return LeaveUserIdValue;
    }

    TSharedPtr<FLeaveNotification> FLeaveNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLeaveNotification>()
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGatheringName(Data->HasField("gatheringName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("gatheringName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLeaveUserId(Data->HasField("leaveUserId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("leaveUserId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
