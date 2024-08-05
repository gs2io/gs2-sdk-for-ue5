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

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"

namespace Gs2::Log::Model
{
    class GS2LOG_API FInsight final : public Gs2Object, public TSharedFromThis<FInsight>
    {
        TOptional<FString> InsightIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> TaskIdValue;
        TOptional<FString> HostValue;
        TOptional<FString> PasswordValue;
        TOptional<FString> StatusValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FInsight();
        FInsight(
            const FInsight& From
        );
        virtual ~FInsight() override = default;

        TSharedPtr<FInsight> WithInsightId(const TOptional<FString> InsightId);
        TSharedPtr<FInsight> WithName(const TOptional<FString> Name);
        TSharedPtr<FInsight> WithTaskId(const TOptional<FString> TaskId);
        TSharedPtr<FInsight> WithHost(const TOptional<FString> Host);
        TSharedPtr<FInsight> WithPassword(const TOptional<FString> Password);
        TSharedPtr<FInsight> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FInsight> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FInsight> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetInsightId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetTaskId() const;
        TOptional<FString> GetHost() const;
        TOptional<FString> GetPassword() const;
        TOptional<FString> GetStatus() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetInsightNameFromGrn(const FString Grn);

        static TSharedPtr<FInsight> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FInsight, ESPMode::ThreadSafe> FInsightPtr;
}