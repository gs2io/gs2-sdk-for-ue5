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

#include "Version/Domain/Model/Gs2VersionEzCheckerGameSessionDomain.h"

namespace Gs2::UE5::Version::Domain::Model
{

    TOptional<FString> FEzCheckerGameSessionDomain::ProjectToken() const
    {
        return Domain->ProjectToken;
    }

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> FEzCheckerGameSessionDomain::Warnings() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>>();
            for (auto Value : *Domain->Warnings) {
                Gs2::UE5::Version::Model::FEzStatus::FromModel(
                    Value
                );
            }
            return Result;
        }();
    }

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>> FEzCheckerGameSessionDomain::Errors() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzStatus>>>();
            for (auto Value : *Domain->Errors) {
                Gs2::UE5::Version::Model::FEzStatus::FromModel(
                    Value
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzCheckerGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzCheckerGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzCheckerGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCheckerGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzCheckerGameSessionDomain::FEzCheckerGameSessionDomain(
        Gs2::Version::Domain::Model::FCheckerAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzCheckerGameSessionDomain::FCheckVersionTask::FCheckVersionTask(
        TSharedPtr<FEzCheckerGameSessionDomain> Self,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzTargetVersion>>> TargetVersions
    ): Self(Self), TargetVersions(TargetVersions)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCheckerGameSessionDomain::FCheckVersionTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Version::Domain::Model::FEzCheckerGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FCheckVersionTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->CheckVersion(
                    MakeShared<Gs2::Version::Request::FCheckVersionRequest>()
                        ->WithTargetVersions([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Version::Model::FTargetVersion>>>();
                            if (!TargetVersions.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *TargetVersions) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Version::Domain::Model::FEzCheckerGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzCheckerGameSessionDomain::FCheckVersionTask>> FEzCheckerGameSessionDomain::CheckVersion(
        TOptional<TArray<TSharedPtr<Gs2::UE5::Version::Model::FEzTargetVersion>>> TargetVersions
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCheckVersionTask>>(
            this->AsShared(),
            TargetVersions
        );
    }
}
