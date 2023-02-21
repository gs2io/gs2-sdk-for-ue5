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
    class GS2VERSION_API FTargetVersion final : public TSharedFromThis<FTargetVersion>
    {
        TOptional<FString> VersionNameValue;
        TSharedPtr<FVersion> VersionValue;
        TOptional<FString> BodyValue;
        TOptional<FString> SignatureValue;

    public:
        FTargetVersion();
        FTargetVersion(
            const FTargetVersion& From
        );
        ~FTargetVersion() = default;

        TSharedPtr<FTargetVersion> WithVersionName(const TOptional<FString> VersionName);
        TSharedPtr<FTargetVersion> WithVersion(const TSharedPtr<FVersion> Version);
        TSharedPtr<FTargetVersion> WithBody(const TOptional<FString> Body);
        TSharedPtr<FTargetVersion> WithSignature(const TOptional<FString> Signature);

        TOptional<FString> GetVersionName() const;
        TSharedPtr<FVersion> GetVersion() const;
        TOptional<FString> GetBody() const;
        TOptional<FString> GetSignature() const;


        static TSharedPtr<FTargetVersion> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FTargetVersion, ESPMode::ThreadSafe> FTargetVersionPtr;
}