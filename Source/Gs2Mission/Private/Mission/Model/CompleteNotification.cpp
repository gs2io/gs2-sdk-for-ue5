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

#include "Mission/Model/CompleteNotification.h"

namespace Gs2::Mission::Model
{

    TSharedPtr<FCompleteNotification> FCompleteNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FCompleteNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FCompleteNotification> FCompleteNotification::WithGroupName(
        const TOptional<FString> GroupName
    ) {
        GroupNameValue = GroupName;
        return SharedThis(this);
    }
    TOptional<FString> FCompleteNotification::GetGroupName() const
    {
        return GroupNameValue;
    }

    TSharedPtr<FCompleteNotification> FCompleteNotification::WithTaskName(
        const TOptional<FString> TaskName
    ) {
        TaskNameValue = TaskName;
        return SharedThis(this);
    }
    TOptional<FString> FCompleteNotification::GetTaskName() const
    {
        return TaskNameValue;
    }

    TSharedPtr<FCompleteNotification> FCompleteNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FCompleteNotification>()
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGroupName(Data->HasField("groupName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("groupName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTaskName(Data->HasField("taskName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("taskName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
