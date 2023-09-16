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

namespace Gs2::AdReward::Model
{
    class GS2ADREWARD_API FPoint final : public Gs2Object, public TSharedFromThis<FPoint>
    {
        TOptional<FString> PointIdValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> PointValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FPoint();
        FPoint(
            const FPoint& From
        );
        virtual ~FPoint() override = default;

        TSharedPtr<FPoint> WithPointId(const TOptional<FString> PointId);
        TSharedPtr<FPoint> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FPoint> WithPoint(const TOptional<int64> Point);
        TSharedPtr<FPoint> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FPoint> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FPoint> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetPointId() const;
        TOptional<FString> GetUserId() const;
        TOptional<int64> GetPoint() const;
        FString GetPointString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetUserIdFromGrn(const FString Grn);

        static TSharedPtr<FPoint> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPoint, ESPMode::ThreadSafe> FPointPtr;
}