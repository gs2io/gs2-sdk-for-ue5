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


#include "Core/Net/Rest/Gs2RestSession.h"

#include "Core/Model/Region.h"
#include "Core/Net/Rest/Task/RestOpenTask.h"
#include "Core/Net/Rest/Task/RestCloseTask.h"
#include "Core/Net/Rest/Task/RestReOpenTask.h"

namespace Gs2::Core::Net::Rest
{
    FGs2RestSession::FGs2RestSession(
        const Model::FGs2CredentialPtr Credential
    ): CredentialValue(Credential), Region(Model::ERegion::ApNorthEast1), OwnerIdValue("")
    {
        
    }

    FGs2RestSession::FGs2RestSession(
        const FGs2RestSession& From
    ): CredentialValue(From.CredentialValue), Region(From.Region), OwnerIdValue("")
    {
    }

    FGs2RestSession::FGs2RestSession(
        const Model::FGs2CredentialPtr Credential,
        const Model::ERegion Region
    ): CredentialValue(Credential), Region(Region), OwnerIdValue("")
    {
        
    }

    TSharedPtr<FAsyncTask<Task::FRestOpenTask>> FGs2RestSession::Open()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FRestOpenTask>>(SharedThis(this));
    }

    TSharedPtr<FAsyncTask<Task::FRestReOpenTask>> FGs2RestSession::ReOpen()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FRestReOpenTask>>(SharedThis(this));
    }

    TSharedPtr<FAsyncTask<Task::FRestCloseTask>> FGs2RestSession::Close()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FRestCloseTask>>(SharedThis(this));
    }

    FString FGs2RestSession::OwnerId() const
    {
        return OwnerIdValue;
    }

    void FGs2RestSession::SetOwnerId(FString OwnerId)
    {
        OwnerIdValue = OwnerId;
    }

    Model::FGs2CredentialPtr FGs2RestSession::Credential() const
    {
        return CredentialValue;
    }

    FString FGs2RestSession::RegionName() const
    {
        switch (Region)
        {
        case Model::ApNorthEast1:
            return "ap-northeast-1";
        case Model::UsEast1:
            return "us-east-1";
        case Model::EuWest1:
            return "eu-west-1";
        case Model::ApSouthEast1:
            return "ap-southeast-1";
        }
        return "unknown";
    }
}
