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
#include "VersionModel.h"
#include "Version.h"

namespace Gs2::Version::Model
{
    class GS2VERSION_API FStatus final : public FGs2Object, public TSharedFromThis<FStatus>
    {
        TSharedPtr<FVersionModel> VersionModelValue;
        TSharedPtr<FVersion> CurrentVersionValue;

    public:
        FStatus();
        FStatus(
            const FStatus& From
        );
        virtual ~FStatus() override = default;

        TSharedPtr<FStatus> WithVersionModel(const TSharedPtr<FVersionModel> VersionModel);
        TSharedPtr<FStatus> WithCurrentVersion(const TSharedPtr<FVersion> CurrentVersion);

        TSharedPtr<FVersionModel> GetVersionModel() const;
        TSharedPtr<FVersion> GetCurrentVersion() const;


        static TSharedPtr<FStatus> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FStatus, ESPMode::ThreadSafe> FStatusPtr;
}