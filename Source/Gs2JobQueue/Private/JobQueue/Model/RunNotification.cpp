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

#include "JobQueue/Model/RunNotification.h"

namespace Gs2::JobQueue::Model
{

    TSharedPtr<FRunNotification> FRunNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FRunNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FRunNotification> FRunNotification::WithJobName(
        const TOptional<FString> JobName
    ) {
        JobNameValue = JobName;
        return SharedThis(this);
    }
    TOptional<FString> FRunNotification::GetJobName() const
    {
        return JobNameValue;
    }

    TSharedPtr<FRunNotification> FRunNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRunNotification>()
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("namespaceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithJobName(Data->HasField("jobName") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("jobName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
