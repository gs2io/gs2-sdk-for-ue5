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
#include "Version.h"

namespace Gs2::Version::Model
{
    class GS2VERSION_API FSignTargetVersion final : public TSharedFromThis<FSignTargetVersion>
    {
        TOptional<FString> RegionValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> VersionNameValue;
        TSharedPtr<FVersion> VersionValue;

    public:
        FSignTargetVersion();
        FSignTargetVersion(
            const FSignTargetVersion& From
        );
        ~FSignTargetVersion() = default;

        TSharedPtr<FSignTargetVersion> WithRegion(const TOptional<FString> Region);
        TSharedPtr<FSignTargetVersion> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FSignTargetVersion> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FSignTargetVersion> WithVersion(const TSharedPtr<FVersion> Version);

        TOptional<FString> GetRegion() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetVersionName() const;
        TSharedPtr<FVersion> GetVersion() const;


        static TSharedPtr<FSignTargetVersion> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSignTargetVersion, ESPMode::ThreadSafe> FSignTargetVersionPtr;
}