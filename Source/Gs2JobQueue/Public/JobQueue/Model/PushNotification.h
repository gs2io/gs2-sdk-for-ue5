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

namespace Gs2::JobQueue::Model
{
	class GS2JOBQUEUE_API FPushNotification : public TSharedFromThis<FPushNotification>
	{
	public:
        TOptional<FString> NamespaceNameValue;

        TSharedPtr<FPushNotification> WithNamespaceName(
            const TOptional<FString> NamespaceName
        );
        TOptional<FString> GetNamespaceName() const;

        static TSharedPtr<FPushNotification> FromJson(const TSharedPtr<FJsonObject> Data);
    };

    typedef TSharedPtr<FPushNotification> FPushNotificationPtr;
}
