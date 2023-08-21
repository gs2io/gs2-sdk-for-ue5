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

namespace Gs2::News::Model
{
    class GS2NEWS_API FProgress final : public Gs2Object, public TSharedFromThis<FProgress>
    {
        TOptional<FString> ProgressIdValue;
        TOptional<FString> UploadTokenValue;
        TOptional<int32> GeneratedValue;
        TOptional<int32> PatternCountValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FProgress();
        FProgress(
            const FProgress& From
        );
        virtual ~FProgress() override = default;

        TSharedPtr<FProgress> WithProgressId(const TOptional<FString> ProgressId);
        TSharedPtr<FProgress> WithUploadToken(const TOptional<FString> UploadToken);
        TSharedPtr<FProgress> WithGenerated(const TOptional<int32> Generated);
        TSharedPtr<FProgress> WithPatternCount(const TOptional<int32> PatternCount);
        TSharedPtr<FProgress> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FProgress> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FProgress> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetProgressId() const;
        TOptional<FString> GetUploadToken() const;
        TOptional<int32> GetGenerated() const;
        FString GetGeneratedString() const;
        TOptional<int32> GetPatternCount() const;
        FString GetPatternCountString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUploadTokenFromGrn(const FString Grn);

        static TSharedPtr<FProgress> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FProgress, ESPMode::ThreadSafe> FProgressPtr;
}