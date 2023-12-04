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

#include "Version/Domain/Model/Gs2VersionEzCheckerDomain.h"

namespace Gs2::UE5::Version::Domain::Model
{

    TOptional<FString> FEzCheckerDomain::ProjectToken() const
    {
        return Domain->ProjectToken;
    }

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> FEzCheckerDomain::Warnings() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>>();
            for (auto Value : *Domain->Warnings) {
                Result->Add(
                    Gs2::UE5::Version::Model::FEzStatus::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> FEzCheckerDomain::Errors() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>>();
            for (auto Value : *Domain->Errors) {
                Result->Add(
                    Gs2::UE5::Version::Model::FEzStatus::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzCheckerDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzCheckerDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzCheckerDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCheckerDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzCheckerDomain::FEzCheckerDomain(
        Gs2::Version::Domain::Model::FCheckerDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }
}
