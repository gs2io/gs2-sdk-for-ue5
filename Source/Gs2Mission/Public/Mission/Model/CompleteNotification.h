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

#pragma once

namespace Gs2::Mission::Model
{
	class GS2MISSION_API FCompleteNotification : public TSharedFromThis<FCompleteNotification>
	{
	public:
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GroupNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> TaskNameValue;

        TSharedPtr<FCompleteNotification> WithNamespaceName(
            const TOptional<FString> NamespaceName
        );
        TOptional<FString> GetNamespaceName() const;

        TSharedPtr<FCompleteNotification> WithGroupName(
            const TOptional<FString> GroupName
        );
        TOptional<FString> GetGroupName() const;

        TSharedPtr<FCompleteNotification> WithUserId(
            const TOptional<FString> UserId
        );
        TOptional<FString> GetUserId() const;

        TSharedPtr<FCompleteNotification> WithTaskName(
            const TOptional<FString> TaskName
        );
        TOptional<FString> GetTaskName() const;

        static TSharedPtr<FCompleteNotification> FromJson(const TSharedPtr<FJsonObject> Data);
    };

    typedef TSharedPtr<FCompleteNotification> FCompleteNotificationPtr;
}
